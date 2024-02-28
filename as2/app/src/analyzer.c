#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "sampler.h"
#include "analyzer.h"

#define DISTANCE_THRESHOLD 0.1
#define HYSTERESIS_THRESHOLD 0.03

//counting the number of dips in dataset  
int Analyzer_analyzeDips(){
    bool overThreshold = false;
    int dipCount = 0;
    int size = 0;
    double* lightData = Sampler_getHistory(&size);
    double average = Sampler_getAverageReading();

    for (int i = 0; i< size; i++){
        if(lightData[i] < average){
            if(overThreshold == false)
            dipCount = 1;
        }
    }
    
return dipCount;
}