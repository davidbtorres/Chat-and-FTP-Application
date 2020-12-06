/*
Project 2
Networking
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

#define PORT 5000
#define BUFFERSIZE 1024

int main(void)
{
	int socketFD;
	struct sockaddr_in6 serverAddr;
	char buffer[BUFFERSIZE];
	socklen_t addressSize;
	int isRunning = 1;


	socketFD = socket(AF_INET, SOCK_DGRAM, 0);

	if (socketFD < 0)
	{
		perror("Could not create socket.");
		exit(1);
	}

	memset(&serverAddr, '\0', sizeof(serverAddr));

	serverAddr.sin6_family = AF_INET;
	serverAddr.sin6_port = htons(PORT);
	inet_pton(AF_INET6, "2601:8c1:8382:2070::6239", &serverAddr.sin6_addr);
  	//serverAddr.sin_addr.s_addr = inet_addr("73.98.17.121");

    bind(socketFD, (struct sockaddr*) &serverAddr, sizeof(serverAddr));

    while (isRunning)
    {
    	scanf("%s", buffer);
    	sendto(socketFD, buffer, BUFFERSIZE, MSG_CONFIRM, (struct sockaddr*) &serverAddr, sizeof(serverAddr));
    	addressSize = sizeof(serverAddr);
    	recvfrom(socketFD, buffer, BUFFERSIZE, MSG_WAITALL, (struct sockaddr*) &serverAddr, &addressSize);
    	printf("%s\n", buffer);
    }
}