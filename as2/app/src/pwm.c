#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include "timer.h"
#include "pwm.h"
#include "sampler.h"
#include "terminate.h"

#define LED_RED_PERIOD "/dev/bone/pwm/1/b/period"
#define LED_GREEN_PERIOD "/dev/bone/pwm/2/a/period"
#define LED_BLUE_PERIOD "/dev/bone/pwm/1/a/period"

#define LED_RED_ENABLE "/dev/bone/pwm/1/b/enable"
#define LED_GREEN_ENABLE "/dev/bone/pwm/2/a/enable"
#define LED_BLUE_ENABLE "/dev/bone/pwm/1/a/enable"

#define LED_RED_DUTY_CYCLE "/dev/bone/pwm/1/b/duty_cycle"
#define LED_GREEN_DUTY_CYCLE "/dev/bone/pwm/2/a/duty_cycle"
#define LED_BLUE_DUTY_CYCLE "/dev/bone/pwm/1/a/duty_cycle"

#define BUFFER_SIZE 20
#define COLOUR_PRESET 50000

pthread_t pwmThread;

static void* LEDViaPWM();

//runCommand function taken from assignment page
void runCommand(char* command){
    // Execute the shell command (output into pipe)
    FILE *pipe = popen(command, "r");
    // Ignore output of the command; but consume it
    // so we don't get an error when closing the pipe.
    char buffer[1024];
    while (!feof(pipe) && !ferror(pipe)) {
    if (fgets(buffer, sizeof(buffer), pipe) == NULL)
        break;
        // printf("--> %s", buffer); // Uncomment for debugging
    }
    // Get the exit code from the pipe; non-zero is an error:
    int exitCode = WEXITSTATUS(pclose(pipe));
    if (exitCode != 0) {
        perror("Unable to execute command:");
        printf(" command: %s\n", command);
        printf(" exit code: %d\n", exitCode);
    }
}


bool WriteToFile(char* FilePath, char* contents){
	FILE *FileVar = fopen(FilePath, "w");
    if (FileVar == NULL) {
        printf("ERROR OPENING %s.", FilePath);
        return false;
        }
    int charWritten = fprintf(FileVar, contents);
    if (charWritten <= 0) {
        printf("ERROR WRITING DATA");
        return false;
        }
    fclose(FileVar);     
    return true;
	
}

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
    return WriteToFile(LEDPath, "0");
}

//Turn PWM LEDs On
bool PWMledsOn(char* LEDPath){
	return WriteToFile(LEDPath, "1");
    
}

//Change the frequency of LEDs with PWM
bool ChangePWMFrequency(int frequency){	
	bool status;
    char charFrequency[BUFFER_SIZE];
	sprintf(charFrequency, "%d", frequency);
	status = WriteToFile(LED_RED_PERIOD, charFrequency);
    
	if(status == false){
		return false;
	}
	
	sprintf(charFrequency, "%d", frequency);
	status = WriteToFile(LED_GREEN_PERIOD, charFrequency);
    
	if(status == false){
		return false;
	}sprintf(charFrequency, "%d", frequency);
	status = WriteToFile(LED_BLUE_PERIOD, charFrequency);
    
	if(status == false){
		return false;
	}
	
    return true;
	
}

//Change the LED colour to purple
bool SetPWMledPurple(){
	bool status;
    char charHold[BUFFER_SIZE];
	sprintf(charHold, "%d", COLOUR_PRESET);
	status = WriteToFile(LED_RED_DUTY_CYCLE, charHold);
    
	if(status == false){
		return false;
	}
	
	status = WriteToFile(LED_GREEN_DUTY_CYCLE, "0");
    
	if(status == false){
		return false;
	}

	status = WriteToFile(LED_BLUE_DUTY_CYCLE, charHold);
    
	if(status == false){
		return false;
	}	
	
    return true;
}

//Check the period of the LED to determine 
//whether to switch or not to switch
int CheckPWMFrequency(void){
	FILE *pFile = fopen(LED_BLUE_PERIOD, "r");
	if (pFile == NULL) {
		printf("ERROR: Unable to open file (%s) for read\n", LED_BLUE_PERIOD);
		return -1;
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
static void *LEDViaPWM(){
	
	long long timeCurr = 0;
	long long timePrev = -1001;
	int PWMFrequency = 0;
	//bool status;
	
	//Config LED before starting
	configLED();
	PWMledsOn(LED_RED_PERIOD);
	PWMledsOn(LED_GREEN_PERIOD);
	PWMledsOn(LED_BLUE_PERIOD);
	SetPWMledPurple();
	
	while(getTerminateStatus() == false){
		timeCurr = getTimeInMs();
		if(timeCurr > timePrev + 100){			
			
			//Reset time current to continue checking for time
			timePrev = timeCurr;
			PWMFrequency = CalculatePWMFrequency();
			if(CheckPWMFrequency() != PWMFrequency && CheckPWMFrequency() != -1){
				ChangePWMFrequency(PWMFrequency);					
			}				
		}
	}
	
	PWMledsOff(LED_RED_PERIOD);
	PWMledsOff(LED_GREEN_PERIOD);
	PWMledsOff(LED_BLUE_PERIOD);
	
	return NULL;
}