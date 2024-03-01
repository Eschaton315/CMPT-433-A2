#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "hal/i2c.h"
#include "analyzer.h"
#include "terminate.h"
#include "timer.h"

#define SLEEP_TIME 5
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
		DisplayLeftDigit();
		ChangeDigit(dips / 10);
		sleepForMs(SLEEP_TIME);
		
		DisplayRightDigit();
		ChangeDigit(dips % 10);
		sleepForMs(SLEEP_TIME);
	}
	return NULL;
}