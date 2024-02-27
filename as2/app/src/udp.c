#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include "udp.h"
#include "terminate.h"

//Defined for UDP
#define PORT 12345
#define REPLY_MAX_SIZE 1500
#define RECEIVED_MAX_SIZE 1024

//Commands defined
#define COM_HELP "help"
#define COM_QUESTION "?"
#define COM_COUNT "count"
#define COM_LEN "length"
#define COM_DIPS "dips"
#define COM_HIST "history"
#define COM_STOP "stop"


static pthread_t threadID;
static char replyBuffer[REPLY_MAX_SIZE];
static char MessagePrev[MAX_RECEIVE_MESSAGE_LENGTH];


//Creates the thread for UDP Listen
void UDPThreadCreate(void){
	pthread_create(&threadID, NULL, &UDPListen, NULL);
}

//Runs join to successfully close the thread
void UDPThreadJoin(void){
	pthread_join(threadID, NULL);
}

//Fnction for listening to UDP packets
void *UDPListen(void *args){
	
	
	char message[RECEIVED_MAX_SIZE];
	MessagePrev[0] = 0;
	
	//From Lecture notes set 6
	//Grabs the address, creates socket, 
	//and binds socket to port
	struct sockaddr_in sin;
	int sinLen;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = htonl(INADDR_ANY);	
	sin.sin_port = htons(PORT);	
	
	int socket_descriptor = socket(PF_INET, SOCK_DGRAM, 0);
	bind(socket_descriptor, (struct sockaddr*) &sin, sizeof(sin));

	while(!GetTerminate Status()){
		
		
	}
}

void RunCommand(char* command, int socketDesc, struct sockaddr_in *pSin);

