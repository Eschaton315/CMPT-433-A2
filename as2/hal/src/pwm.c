#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "timer.h"
#include "pwm.h"
#include "sampler.h"

pthread_t pwmThread;