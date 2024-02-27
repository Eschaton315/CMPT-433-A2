#ifndef _UDP_H_
#define _UDP_H_

//Creates the thread for UDP Listen
void UDPThreadCreate(void);

//Runs join to successfully close the thread
void UDPThreadJoin(void);

//Function for listening to UDP packets
void *UDPListen(void *args);

//Function for finding what command was requested 
//and running said command
void RunCommand(char* command, int socketDesc, struct sockaddr_in *pSin);




#endif