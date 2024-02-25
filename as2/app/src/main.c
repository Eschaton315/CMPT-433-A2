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

    Sampler_init();

    sleepForMs(3000);

    Sampler_cleanup();

    printf("Done\n");

    return 0;
}