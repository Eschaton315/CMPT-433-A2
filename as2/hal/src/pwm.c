#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include "app/timer.h"
#include "pwm.h"
#include "sampler.h"
#include "hal/joyStick.h"

#define LED_RED_PERIOD "/dev/bone/pwm/1/b/period"
#define LED_GREEN_PERIOD "/dev/bone/pwm/2/a/period"
#define LED_BLUE_PERIOD "/dev/bone/pwm/1/a/period"

#define LED_RED_ENABLE "/dev/bone/pwm/1/b/enable"
#define LED_GREEN_ENABLE "/dev/bone/pwm/2/a/enable"
#define LED_BLUE_ENABLE "/dev/bone/pwm/1/a/enable"

#define LED_RED_DUTY_CYCLE "/dev/bone/pwm/1/b/duty_cycle"
#define LED_GREEN_DUTY_CYCLE "/dev/bone/pwm/2/a/duty_cycle"
#define LED_BLUE_DUTY_CYCLE "/dev/bone/pwm/1/a/duty_cycle"

pthread_t pwmThread;

static void* LEDViaPWM();


//configure pin to LED
void configLED(void){
	runCommand("config-pin P9_14 pwm");
	runCommand("config-pin P9_16 pwm");
	runCommand("config-pin P8_19 pwm");
}

//Creates the thread for pwm
void pwmThreadCreate(void){
	pthread_create(&pwmThread, NULL, &LEDViaPWM, NULL);
}

//Runs join to successfully close the thread
void pwmThreadJoin(void){
	pthread_join(pwmThread, NULL);
}

//Calculate PWMFrequency
int CalculatePWMFrequency(void){
	int histSize = 1;
	double* histArr = Sampler_getHistory(&histSize);
	int PWMValue = (int) histArr[0];
	PWMValue = PWMValue / 40;
	
	return PWMValue;
}

//Turn PWM LEDs Off
bool PWMledsOff(char* LEDPath){

    FILE *LEDPathFile = fopen(LEDPath, "w");
    if (LEDPathFile == NULL) {
        printf("ERROR OPENING %s.", LEDPath);
        return false;
        }
    int charWritten = fprintf(LEDPathFile, "0");
    if (charWritten <= 0) {
        printf("ERROR WRITING DATA");
        return false;
        }
    fclose(LEDPathFile);     
    return true;
}

//Turn PWM LEDs On
bool PWMledsOn(char* LEDPath){

    FILE *LEDPathFile = fopen(LEDPath, "w");
    if (LEDPathFile == NULL) {
        printf("ERROR OPENING %s.", LEDPath);
        return false;
        }
    int charWritten = fprintf(LEDPathFile, "1");
    if (charWritten <= 0) {
        printf("ERROR WRITING DATA");
        return false;
        }
    fclose(LEDPathFile);     
    return true;
}

//Change the frequency of LEDs with PWM
void ChangePWMFrequency(int frequency){
	FILE *LEDPathFile = fopen(LED_RED_PERIOD, "w");
    if (LEDPathFile == NULL) {
        printf("ERROR OPENING %s.", LED_RED_PERIOD);
        return false;
        }
    int charWritten = fprintf(LEDPathFile, "%d", frequency);
    if (charWritten <= 0) {
        printf("ERROR WRITING DATA");
        return false;
        }
    fclose(LEDPathFile);     
	
	LEDPathFile = fopen(LED_GREEN_PERIOD, "w");
    if (LEDPathFile == NULL) {
        printf("ERROR OPENING %s.", LED_GREEN_PERIOD);
        return false;
        }
    int charWritten = fprintf(LEDPathFile, "%d", frequency);
    if (charWritten <= 0) {
        printf("ERROR WRITING DATA");
        return false;
        }
    fclose(LEDPathFile);
	
	LEDPathFile = fopen(LED_BLUE_PERIOD, "w");
    if (LEDPathFile == NULL) {
        printf("ERROR OPENING %s.", LED_BLUE_PERIOD);
        return false;
        }
    int charWritten = fprintf(LEDPathFile, "%d", frequency);
    if (charWritten <= 0) {
        printf("ERROR WRITING DATA");
        return false;
        }
    fclose(LEDPathFile);
	
	
    return true;
	
}

//Change the LED colour to purple
void SetPWMledPurple(void){
	FILE *LEDPathFile = fopen(LED_RED_DUTY_CYCLE, "w");
    if (LEDPathFile == NULL) {
        printf("ERROR OPENING %s.", LED_RED_DUTY_CYCLE);
        return false;
        }
    int charWritten = fprintf(LEDPathFile, "50000");
    if (charWritten <= 0) {
        printf("ERROR WRITING DATA");
        return false;
        }
    fclose(LEDPathFile);     
	
	LEDPathFile = fopen(LED_GREEN_DUTY_CYCLE, "w");
    if (LEDPathFile == NULL) {
        printf("ERROR OPENING %s.", LED_GREEN_DUTY_CYCLE);
        return false;
        }
    int charWritten = fprintf(LEDPathFile, "0");
    if (charWritten <= 0) {
        printf("ERROR WRITING DATA");
        return false;
        }
    fclose(LEDPathFile);
	
	LEDPathFile = fopen(LED_BLUE_DUTY_CYCLE, "w");
    if (LEDPathFile == NULL) {
        printf("ERROR OPENING %s.", LED_BLUE_DUTY_CYCLE);
        return false;
        }
    int charWritten = fprintf(LEDPathFile, "50000");
    if (charWritten <= 0) {
        printf("ERROR WRITING DATA");
        return false;
        }
    fclose(LEDPathFile);
	
	
    return true;
}

//Check the period of the LED to determine 
//whether to switch or not to switch
int CheckPWMFrequency(void){
	FILE *pFile = fopen(LED_BLUE_PERIOD, "r");
	if (pFile == NULL) {
		printf("ERROR: Unable to open file (%s) for read\n", LED_BLUE_PERIOD);
		return false;
	}
	// Read string (line)

	const int MAX_LENGTH = 1024;
	char buff[MAX_LENGTH];
	fgets(buff, MAX_LENGTH, pFile);
	// Close
	fclose(pFile);

	int value = atoi(buff);
	return value;
	
}

//Function for running the PWM
static void *LEDViaPWM*(){
	
	long long timeCurr = 0;
	long long timePrev = -1001;
	int PWMFrequency = 0;
	bool status;
	
	//Config LED before starting
	configLED();
	status = PWMledOn(LED_RED_PERIOD);
	status = PWMledOn(LED_GREEN_PERIOD);
	status = PWMledOn(LED_BLUE_PERIOD);
	SetPWMledPurple();
	
	while(getTerminateStatus() == false){
		timeCurr = getTimeInMs();
		if(timeCurr > timePrev + 100){			
			
			//Reset time current to continue checking for time
			timePrev = timeCurr;
			PWMFrequency = CalculatePWMFrequency();
			if(CheckPWMFrequency() == PWMFrequency){
				ChangePWMFrequency(PWMFrequency);					
			}				
		}
	}
	
	status = PWMledOff(LED_RED_PERIOD);
	status = PWMledOff(LED_GREEN_PERIOD);
	status = PWMledOff(LED_BLUE_PERIOD);
	
	return void;
}