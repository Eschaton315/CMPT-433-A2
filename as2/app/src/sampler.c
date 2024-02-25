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

bool stopSample = false;
int totalSample = 0;
pthread_t samplerThread;

// Header for the function that samples light
static void *sampleThread();

void Sampler_init(){
    FILE *fp = fopen("sampleHistory.txt", "w");
    fclose(fp);
    pthread_create(&samplerThread, NULL, &sampleThread, NULL);
    return;
}

// After one second all saved samples will be moved to sampleHistory.txt
static void MoveSamplesToHistory(double *sampleList){
    int counter = 0;
    FILE *fp = fopen("sampleHistory.txt", "a");
    while (sampleList[counter] != 0){
        fprintf(fp, "%f ", sampleList[counter]);
        counter++;
    }
    fprintf(fp, "\n");
    fclose(fp);
    return;
}

// The function that samples light
static void *sampleThread(){
    while (!stopSample){
        int sample;
        double sampleList[1000];
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

    return 0;
}

double *Sampler_getHistory(int *size){
    double *test = 0;
    if (size[0] == 0){
        test[0] = 0.0;
    }
    else{
        test[0] = 1.0;
    }

    return test;
}

double Sampler_getAverageReading(){
    return 1;
}

long long Sampler_getNumSamplesTaken()
{

    return 0;
}
