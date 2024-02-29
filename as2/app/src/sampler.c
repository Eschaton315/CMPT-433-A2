#include "sampler.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include "timer.h"
#include "periodTimer.h"
#include "analyzer.h"

#define A2D_FILE_VOLTAGE1 "/sys/bus/iio/devices/iio:device0/in_voltage1_raw"
#define A2D_VOLTAGE_REF_V 1.8
#define A2D_MAX_READING 4095
#define SAMPLE_MAX_VALUE 1024
#define HISTORY_FILE "sampleHistory.txt"

// For sample sizes and saving history
bool stopSample = false;
static unsigned long long totalSample = 0;
int prevSampleSize = 0;
double sampleHistory [SAMPLE_MAX_VALUE];
pthread_t samplerThread;
pthread_t analyzeThread;

// For getting average light levels
#define WEIGHT_OLD_SAMPLE 0.999
static double avgVoltage = 1.0;

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
    while (sampleList[counter] != 0){
    sampleHistory[counter] = sampleList[counter];
        counter++;
    }
    prevSampleSize = counter;
    }
    unlock();
    return;
}

// The function that samples light
static void *sampleThread(){
    while (!stopSample){
        int sample;
        double sampleList[SAMPLE_MAX_VALUE] = {0};
        long long currentTime = getTimeInMs();
        int counter = 0;
        enum Period_whichEvent eventSample = PERIOD_EVENT_SAMPLE_LIGHT;
        //Get as many samples within 1 second with minimum 1ms delay
        while (getTimeInMs() < currentTime + 1000){
            FILE *sampleFile = fopen(A2D_FILE_VOLTAGE1, "r");
            if (sampleFile == NULL){
                printf("ERROR OPENING %s.", A2D_FILE_VOLTAGE1);
                exit(-1);
            }
            fscanf(sampleFile, "%d", &sample);
            sampleList[counter] = ((double)sample / A2D_MAX_READING) * A2D_VOLTAGE_REF_V;
            fclose(sampleFile);
            
            //Calculate average via exponential smoothing
            avgVoltage = WEIGHT_OLD_SAMPLE * avgVoltage + (1 - WEIGHT_OLD_SAMPLE) * sampleList[counter];
            counter++;
            totalSample++;
            Period_markEvent(eventSample);
            sleepForMs(1);
        }
        pthread_join(analyzeThread, NULL);
        MoveSamplesToHistory(sampleList);
        pthread_create(&analyzeThread, NULL, &Analyzer_displaySample, NULL);
    }
    return NULL;
}

// Stops the sampling process
void Sampler_cleanup(){
    stopSample = true;
    pthread_join(samplerThread, NULL);

    return;
}

//returns the size of history of the previous second
int Sampler_getHistorySize(){
    return prevSampleSize;
}

double *Sampler_getHistory(int *size){
    //dynamically allocate an array of doubles of all samples in the previous second
    double *historyCopy = 0;
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
    return avgVoltage;
}

long long Sampler_getNumSamplesTaken(){
    return totalSample;
}
