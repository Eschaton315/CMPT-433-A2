#include "udp.h"
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>


//Creates the thread for UDP Listen
void UDPThreadCreate(void);

//Runs join to successfully close the thread
void UDPThreadJoin(void);

//Fnction for listening to UDP packets
void *UDPListen(void *args);

void RunCommand(char* command, int socketDesc, struct sockaddr_in *pSin);

