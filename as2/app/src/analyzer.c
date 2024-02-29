#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "sampler.h"
#include "analyzer.h"
#include "periodTimer.h"

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
void *Analyzer_displaySample(){
    int size = 0;
    double* lightData = Sampler_getHistory(&size);
    double average = Sampler_getAverageReading();
    int totalSamples = Sampler_getNumSamplesTaken();
    int dipCount = Analyzer_analyzeDips();
    
    enum Period_whichEvent eventType = PERIOD_EVENT_SAMPLE_LIGHT;
    Period_statistics_t *pStats = malloc(sizeof *pStats);
    Period_getStatisticsAndClear(eventType, pStats);
    

    //TODO: get POT raw data and its frequency (Hz)

    //First Line displays # of samples, reading from POT, # of dips,
    //and time jitter info from the previous second 
    printf("#Smpl/s = %d    ", totalSamples);
    printf("POT @ <rawPOTData> => <POTFrequency>"   );
    printf("avg = %.3f  ", average);
    printf("dips = %d   ", dipCount);
    printf("Smpl ms[%.3f,%.3f] avg %.3f/%d",pStats->minPeriodInMs,pStats->maxPeriodInMs,pStats->avgPeriodInMs ,pStats->numSamples);
    printf("\n");

    int sampleInterval = 1;
    int count = 0;
    if(size >= 20){
        sampleInterval = size / 20;
    }

    //Second Line prints 20 samples evenly distributed through the sampleHistory 
        for(int i = 0; i<size && count<20;i++){
            if(i % sampleInterval == 0){
                printf("%d:%.3f ",i,lightData[i]);
                count++;
            }
        }
        printf("\n");
    free(lightData);
    free(pStats);
    return NULL;
}