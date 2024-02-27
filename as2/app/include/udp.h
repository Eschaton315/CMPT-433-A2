#ifndef _UDP_H_
#define _UDP_H_

//Creates the thread for UDP Listen
void UDPThreadCreate(void);

//Runs join to successfully close the thread
void UDPThreadJoin(void);

//Fnction for listening to UDP packets
void *UDPListen(void *args);

void RunCommand(char* command, int socketDesc, struct sockaddr_in *pSin);




#endif