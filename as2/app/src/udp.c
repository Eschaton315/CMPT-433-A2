#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include "udp.h"
#include "terminate.h"
#include "sampler.h"

//Defined for UDP
#define PORT 12345
#define REPLY_MAX_SIZE 1500
#define RECEIVED_MAX_SIZE 1024

//Commands defined
#define COM_HELP "help"
#define COM_COUNT "count"
#define COM_LEN "length"
#define COM_DIPS "dips"
#define COM_HIST "history"
#define COM_STOP "stop"
#define COM_REPEAT 10


static pthread_t threadID;
static char reply[REPLY_MAX_SIZE];
static char msgPrev[RECEIVED_MAX_SIZE];
static bool firstCom = true;

//Function for listening to UDP packets
static void *UDPListen(void *args);

//Function for finding what command was requested 
//and running said command
void RunCommand(char* command, int socketDesc, struct sockaddr_in *pSin);

//Checks and find which command was sent
//1 = Help / ?, 2 = count, 3 = len, 4 = dips
//5 = history, 6 = stop, 7 = repeat
static int CheckCommand(char* command);


//Creates the thread for UDP Listen
void UDPThreadCreate(void){
	pthread_create(&threadID, NULL, &UDPListen, NULL);
}

//Runs join to successfully close the thread
void UDPThreadJoin(void){
	pthread_join(threadID, NULL);
}

//get value of firstCom Variable
bool getFirstCom(void){
	return firstCom;
	
}

//get value of firstCom Variable
void changeFirstCom(bool status){
	firstCom = status;
}

//Function for listening to UDP packets
static void *UDPListen(void *args){
	
	
	char msg[RECEIVED_MAX_SIZE];
	msgPrev[0] = 0;
	
	//From Lecture notes set 6
	//Grabs the address, creates socket, 
	//Binds socket to port,
	//Receives data, sends reply if needed
	struct sockaddr_in sin;
	unsigned int sinLen;
	int bytesRx;
	
	//Grabbing necessary data for socket
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = htonl(INADDR_ANY);	
	sin.sin_port = htons(PORT);	
	
	//binding socket
	int socket_descriptor = socket(PF_INET, SOCK_DGRAM, 0);
	bind(socket_descriptor, (struct sockaddr*) &sin, sizeof(sin));

	while(getTerminateStatus() == false){
		
		//receiving packets
		sinLen = sizeof(sin);		
		bytesRx = recvfrom(socket_descriptor, msg, RECEIVED_MAX_SIZE, 0, (struct sockaddr *) &sin, &sinLen);
		
		msg[bytesRx] = 0;
		
		RunCommand(msg, socket_descriptor, &sin);
		
		//send reply if necessary
		if(strlen(reply) > 0){
			sinLen = sizeof(sin);
			sendto(socket_descriptor, reply, strlen(reply),(struct sockaddr *) &sin, sinLen);
			
		} 
	}
	
	close(socket_descriptor);
	return NULL;
}

//Checking message to see what command was sent
//1 = Help / ?, 2 = count, 3 = len, 4 = dips
//5 = history, 6 = stop, 7 = repeat, 8 = invalid
static int CheckCommand(char* command){
	
	//Repeat has no string to compare to 
	if(command[0] == COM_REPEAT){
		return 7;
	}
	
	//Compare command to message to return what command was sent
	if(strncmp(command, COM_HELP, strlen(COM_HELP)) == 0){
		return 1;
	}
	
	if(strncmp(command, COM_COUNT, strlen(COM_COUNT)) == 0){
		return 2;
	}
	
	if(strncmp(command, COM_LEN, strlen(COM_LEN)) == 0){
		return 3;
	}
	
	if(strncmp(command, COM_DIPS, strlen(COM_DIPS)) == 0){
		return 4;
	}
	
	if(strncmp(command, COM_HIST, strlen(COM_HIST)) == 0){
		return 5;
	}
	
	if(strncmp(command, COM_STOP, strlen(COM_STOP)) == 0){
		return 6;
	}
		
	//if none of the strings are equal, then it is invalid
	return 8;
}

//Check the message and run the command in the message
static void RunCommand(char* command, int socketDesc, struct sockaddr_in *sinGiven){
	
	reply[0] = 0;	
	int commandCode = CheckCommand(command);
	//Will place the necessary data in reply arr
	//Based on every command
	switch (commandCode) {		
		//help
		case 1:
			sprintf(reply, 
			"Accepted command examples:\n"
			"help / ?    -- get brief summary/list of supported commands.\n"
			"count       -- get the total number of samples taken.\n"
			"length      -- get the number of samples taken in the previously completed second.\n"
			"dips        -- get the number of dips in the previously completed second.\n"
			"history     -- get all the samples in the previously completed second.\n"
			"stop        -- cause the server program to end.\n"
			"<enter>     -- repeat last command.\n");			
			break;
		
		//count
		case 2:
			sprintf(reply, "# samples taken total: %lld\n", Sampler_getNumSamplesTaken());
			break;
			
		//len
		case 3:
			sprintf(reply, "# samples taken last second: %d\n", Sampler_getHistorySize());
			break;
			
		//dips
		case 4:
			//Will be worked on and updated shortly
			
			break;
			
		//hist
		case 5: ;
			int histSize = 0;
			double* histArr = Sampler_getHistory(&histSize);
			
			//Error checking
			if(histSize < 1){
				sprintf(reply, "Error in checking history...");
			}else{
				sprintf(reply, "%.3lf, ", histArr[0]);
				for(int i = 1; i < histSize; i++){
					strncat(reply, "%.3lf, ", histArr[i]);
					if(i % 10 == 0){
						strncat(reply, "\n");
					}
				
				}
			}
			strncat(reply, "\n");
			
			
			break;
			
		//stop
		case 6:
			changeTerminateStatus(true);
			sprintf(reply, "Program terminating.");
			break;
			
		//repeat
		case 7:
		
			if(getFirstCom() == true){
				sprintf(reply, "ERROR! Unknown Command!\n"
				"Accepted command examples:\n"
				"help / ?    -- get brief summary/list of supported commands.\n"
				"count       -- get the total number of samples taken.\n"
				"length      -- get the number of samples taken in the previously completed second.\n"
				"dips        -- get the number of dips in the previously completed second.\n"
				"history     -- get all the samples in the previously completed second.\n"
				"stop        -- cause the server program to end.\n"
				"<enter>     -- repeat last command.\n"
				);
			}else{
				memcpy(command, msgPrev, RECEIVED_MAX_SIZE);
				
			}
			
			break;	
		
		//invalid
		case 8:
			sprintf(reply, "ERROR! Unknown Command!\n"
			"Accepted command examples:\n"
			"help / ?    -- get brief summary/list of supported commands.\n"
			"count       -- get the total number of samples taken.\n"
			"length      -- get the number of samples taken in the previously completed second.\n"
			"dips        -- get the number of dips in the previously completed second.\n"
			"history     -- get all the samples in the previously completed second.\n"
			"stop        -- cause the server program to end.\n"
			"<enter>     -- repeat last command.\n"
			);
			break;
	}
	
	if(commandCode != 7 && commandCode != 8){
		//saved for next use
		memcpy(msgPrev, command, RECEIVED_MAX_SIZE);
		if(getFirstCom() == true){
			changeFirstCom(false);
		}
		
	}
	
}

