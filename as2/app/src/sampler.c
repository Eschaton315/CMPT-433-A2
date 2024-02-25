#include "sampler.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include "timer.h"

#define A2D_FILE_VOLTAGE1 "/sys/bus/iio/devices/iio:device0/in_voltage1_raw"
#define A2D_VOLTAGE_REF_V 1.8
#define A2D_MAX_READING 4095
#define SAMPLE_MAX_VALUE 1024
#define HISTORY_FILE "sampleHistory.txt"

bool stopSample = false;
int totalSample = 0;
int prevSampleSize = 0;
double sampleHistory [SAMPLE_MAX_VALUE];
pthread_t samplerThread;

// Average
#define WEIGHT_OLD_SAMPLE 0.999
//static double s_filterVoltage = 1.0;

// Thread synchronization
static pthread_mutex_t samplerHistoryMutex = PTHREAD_MUTEX_INITIALIZER;

static void lock(){
    pthread_mutex_lock(&samplerHistoryMutex);
}
static void unlock(){
    pthread_mutex_unlock(&samplerHistoryMutex);
}

// Header for the function that samples light
static void *sampleThread();

void Sampler_init(){
    pthread_create(&samplerThread, NULL, &sampleThread, NULL);
    return;
}

// After one second all saved samples will be moved to sampleHistory.txt
static void MoveSamplesToHistory(double *sampleList){
    int counter = 0;
    lock();
    {
    //FILE *fp = fopen(HISTORY_FILE, "a");
    while (sampleList[counter] != 0){
    //    fprintf(fp, "%f ", sampleList[counter]);
    sampleHistory[counter] = sampleList[counter];
    //printf("%f ",sampleHistory[counter]);
        counter++;
    }
    //printf("\n");
    //fprintf(fp, "\n");
    //fclose(fp);
    prevSampleSize = counter;
    }
    unlock();
    return;
}

// The function that samples light
static void *sampleThread(){
    while (!stopSample){
        int sample;
        double sampleList[SAMPLE_MAX_VALUE];
        long long currentTime = getTimeInMs();
        int counter = 0;
        while (getTimeInMs() < currentTime + 1000){
            FILE *sampleFile = fopen(A2D_FILE_VOLTAGE1, "r");
            if (sampleFile == NULL){
                printf("ERROR OPENING %s.", A2D_FILE_VOLTAGE1);
                exit(-1);
            }
            fscanf(sampleFile, "%d", &sample);
            sampleList[counter] = ((double)sample / A2D_MAX_READING) * A2D_VOLTAGE_REF_V;
            fclose(sampleFile);
            sleepForMs(1);
            counter++;
        }
        MoveSamplesToHistory(sampleList);
    }
    return NULL;
}

// Stops the sampling process
void Sampler_cleanup(){
    stopSample = true;
    pthread_join(samplerThread, NULL);

    return;
}

int Sampler_getHistorySize(){
    return prevSampleSize;
}

double *Sampler_getHistory(int *size){
    double *historyCopy = 0;
    printf("getting hist\n");
    lock();
    {
        historyCopy = malloc(sizeof(*sampleHistory)*prevSampleSize);
        for(int i = 0; i<prevSampleSize; i++){
            historyCopy[i] = sampleHistory[i] ;
        }
        *size = prevSampleSize;
    }
    unlock();
    return historyCopy;
}

double Sampler_getAverageReading(){
    return 1;
}

long long Sampler_getNumSamplesTaken()
{
    return 0;
}
