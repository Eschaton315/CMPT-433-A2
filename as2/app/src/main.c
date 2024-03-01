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
#include "udp.h"
#include "pwm.h"
#include "hal/led.h"
#include "hal/joyStick.h"
#include "displayProgram.h" 
#include "hal/i2c.h"

int main()
{
    printf("starting sampling\n");
    Period_init();
    Sampler_init();
    pwmThreadCreate();
    UDPThreadCreate();
	Display2DigitThreadCreate();


    //replace this with the udp listener

    sleepForMs(5500);
	
	Display2DigitThreadJoin();
    UDPThreadJoin();
    pwmThreadJoin();
    Sampler_cleanup();
    Period_cleanup();

    printf("\nDone\n");

    return 0;
}