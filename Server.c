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
	struct sockaddr_in serverAddr, clientAddr;
	char buffer[BUFFERSIZE];
	socklen_t addressSize;
	int numBytes;

	socketFD = socket(AF_INET, SOCK_DGRAM, 0);

	if (socketFD < 0)
	{
		perror("Could not create socket.");
		exit(0);
	}

	memset(&serverAddr, '\0', sizeof(serverAddr));
	memset(&clientAddr, '\0', sizeof(clientAddr));


	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(socketFD, (struct sockaddr*) &serverAddr, sizeof(serverAddr));

	addressSize = sizeof(clientAddr);
	numBytes = recvfrom(socketFD, buffer, BUFFERSIZE, MSG_WAITALL, (struct sockaddr*) &clientAddr, &addressSize);
	buffer[numBytes] = '\0';
  	printf("Data Received: %s", buffer);
  }