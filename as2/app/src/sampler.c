#include "sampler.h"
#include <stdio.h>
#include <stdlib.h>
#include "timer.h"

#define A2D_FILE_VOLTAGE1   "/sys/bus/iio/devices/iio:device0/in_voltage1_raw"

void Sampler_init(){

    FILE* f = fopen (A2D_FILE_VOLTAGE1, "r");
    int sampleValue = 0;
    int sampleList[1000];
    if (f){

    }
    for(int i = 0; i < 1000; i++){
        fscanf(f,"%d",&sampleValue);
        sampleList[i] = sampleValue;
        sleepForMs(1);
    }

return;
}

void Sampler_cleanup(){

return;
}

void Sampler_moveCurrentDataToHistory(){
//FILE *fp;
//fp = fopen ("sampleHistory.txt", "w");

return;
}

int Sampler_getHistorySize(){

return 0;
}

double* Sampler_getHistory(int *size){
    double* test = 0;
    if(size[0]==0){
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

long long Sampler_getNumSamplesTaken(){


    return 0;

}
