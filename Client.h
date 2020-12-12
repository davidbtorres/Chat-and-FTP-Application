#ifndef CLIENT_H_
#define CLIENT_H_

void formatCommand(char option[], char username[], char password[]);
int authenticateCommand(int* socketFD, struct sockaddr_in* serverAddr, socklen_t addressSize);

#endif