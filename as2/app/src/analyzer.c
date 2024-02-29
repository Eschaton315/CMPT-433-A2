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
    return dipCount;
}