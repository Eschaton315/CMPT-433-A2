#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include "timer.h"
#include "sampler.h"
#include "hal/led.h"
#include "hal/joyStick.h"

int main()
{
    printf("starting sampling\n");
    Sampler_init();

    sleepForMs(3000);
    int len = 0;
    double *hist = Sampler_getHistory(&len);
    Sampler_cleanup();
    //test for getHistory function
    for(int i = 0; i < Sampler_getHistorySize(); i++){
        printf("%f",hist[i]);
    }
    free(hist);
    printf("\nDone\n");

    return 0;
}