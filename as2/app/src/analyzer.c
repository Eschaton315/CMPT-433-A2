#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "sampler.h"
#include "analyzer.h"

#define DIFFERENCE_THRESHOLD 0.1
#define HYSTERESIS_THRESHOLD 0.03

//counting the number of dips in dataset  
int Analyzer_analyzeDips(){
    bool overThreshold = false;
    int dipCount = 0;
    int size = 0;
    double* lightData = Sampler_getHistory(&size);
    double average = Sampler_getAverageReading();

    for (int i = 0; i< size; i++){
        double averageDifference = average - lightData[i];
        if(!overThreshold){
            //checks if we are entering a dip
            if(averageDifference > DIFFERENCE_THRESHOLD){
                overThreshold = true;
                dipCount++; 
            }
        }else{
            //checks if we are out of the dip
            if(averageDifference < DIFFERENCE_THRESHOLD - HYSTERESIS_THRESHOLD){
                overThreshold = false;
            }
        }
    }
    free(lightData);
    return dipCount;
}

//Outputs information of teh previous second into the terminal
void Analyzer_displaySample(){
    int size = 0;
    double* lightData = Sampler_getHistory(&size);
    double average = Sampler_getAverageReading();
    int totalSamples = Sampler_getNumSamplesTaken();
    int dipCount = Analyzer_analyzeDips();

    //TODO: get POT raw data and its frequency (Hz)
    //TODO: get Timing jitter information from 1.7

    //First Line
    printf("#Smpl/s = %d    ", size);
    printf("POT @ <rawPOTData> => <POTFrequency>"   );
    printf("dips = %d   ", dipCount);
    printf("Smpl ms[<min>,<max>] avg <average>/%d", size);
    printf("\n");

    int sampleInterval = 1;
    int count = 0;
    if(size >= 20){
        sampleInterval = size / 20;
    }
        for(int i = 0; i<size && count<20;i++){
            if(i % sampleInterval == 0){
                printf("%d:%.3f ");
                count++;
            }
        }
        printf("\n");
    free(lightData);
}