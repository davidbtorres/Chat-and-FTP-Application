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
#include "Server.h"

#define PORT 5000
#define BUFFERSIZE 1024

int main(void)
{
	int socketFD;
	struct sockaddr_in serverAddr, clientAddr;
	socklen_t addressSize;
	int numBytes;
	struct user allUsers[100];
	int numUsers = 0;
	char buffer[BUFFERSIZE];
	int isRunning = 1;

	socketFD = socket(AF_INET, SOCK_DGRAM, 0);

	if (socketFD < 0)
	{
		perror("Could not create socket.");
		exit(1);
	}

	memset(&serverAddr, '\0', sizeof(serverAddr));
	memset(&clientAddr, '\0', sizeof(clientAddr));

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(socketFD, (struct sockaddr*) &serverAddr, sizeof(serverAddr));

	addressSize = sizeof(clientAddr);

	while (isRunning)
	{
		printf("%s\n", "I am running");
		
		numBytes = recvfrom(socketFD, buffer, BUFFERSIZE, MSG_WAITALL, (struct sockaddr*) &clientAddr, &addressSize);

		if (buffer[0] == '0')
		{
			printf("%s\n", "Option 0 was recieved.");

			for (int i = 0; i < numUsers; i++)
			{
				if (allUsers[i].isOnline == 1)
				{
					buffer[i] = allUsers[i].username;
				}
			}

			sendto(socketFD, buffer, BUFFERSIZE, MSG_CONFIRM, (struct sockaddr*) &clientAddr, sizeof(clientAddr));		
		}
	}

	//buffer[numBytes] = '\0';
  	printf("Data Received: %s", buffer);
}






