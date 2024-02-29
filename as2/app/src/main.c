#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include "timer.h"
#include "sampler.h"
#include "analyzer.h"
#include "periodTimer.h"
#include "hal/led.h"
#include "hal/joyStick.h"

int main()
{
    printf("starting sampling\n");
    Period_init();
    Sampler_init();

    //replace this with the udp listener
    sleepForMs(5500);

    Sampler_cleanup();
    Period_cleanup();

    printf("\nDone\n");

    return 0;
}