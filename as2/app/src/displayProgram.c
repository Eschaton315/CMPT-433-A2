#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "hal/i2c.h"
#include "analyzer.h"
#include "terminate.h"
#include "timer.h"

#define SLEEP_TIME 5
#define DIPS_CAP 99
#define DIVISION_NUMBER 10

static pthread_t displayThread;

//Function for displaying 2 digit
static void *Display2Digit();

void Display2DigitThreadCreate(void){
	pthread_create(&displayThread, NULL, &Display2Digit, NULL);
}

//Runs join to successfully close the thread
void Display2DigitThreadJoin(void){
	pthread_join(displayThread, NULL);
}

//function for 
static void *Display2Digit(){
	int dips = 0;
	
	InitializeI2C();
	
	while(getTerminateStatus() == false){
		dips = Analyzer_analyzeDips();
		if(dips > DIPS_CAP){
			dips = DIPS_CAP;
		}
		DisplayLeftDigit();
		ChangeDigit(dips / DIVISION_NUMBER);
		sleepForMs(SLEEP_TIME);
		
		DisplayRightDigit();
		ChangeDigit(dips % DIVISION_NUMBER);
		sleepForMs(SLEEP_TIME);
	}
	return NULL;
}