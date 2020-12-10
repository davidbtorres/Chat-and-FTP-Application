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

struct user allUsers[100];
int numUsers = 0;

int main(void)
{
	int socketFD;
	struct sockaddr_in serverAddr, clientAddr;
	socklen_t addressSize;
	int numBytes;
	
	char* token;
	const char delimiter[2] = ",";
	
	char buffer[BUFFERSIZE];
	char bufferOut[BUFFERSIZE];
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
		printf("%s", "Awaiting client.\n");
		numBytes = recvfrom(socketFD, buffer, BUFFERSIZE, MSG_WAITALL, (struct sockaddr*) &clientAddr, &addressSize);
		printf("%s\n", "DLSKGJSLDKGJ");

		strcpy(bufferOut, buffer);

		token = strtok(buffer, delimiter);
		printf("Token: %s\n", token);

		if (strcmp(token, "0") == 0)
		{
			printf("%s\n", "Option 0 was recieved.");
			memset(bufferOut, '\0', sizeof(buffer));

			for (int i = 0; i < numUsers; i++)
			{
				if (allUsers[i].isOnline == 1)
				{
					strcat(bufferOut, allUsers[i].username);
					strcat(bufferOut, "\n");
				}
			}
		}

		else if (strcmp(token, "register") == 0)
		{
			printf("%s\n", "Register option executed.");
			token = strtok(NULL, delimiter);
			printf("Token: %s\n", token);
			strcpy(allUsers[numUsers].username, token);

			token = strtok(NULL, delimiter);
			printf("Token: %s\n", token);
			strcpy(allUsers[numUsers].password, token);

			allUsers[numUsers].isOnline = 0;
			numUsers++;
			
			strcpy(bufferOut, "From Server: Successfully registered");
		}

		else if (strcmp(token, "signin") == 0)
		{
			printf("%s\n", "Signin option executed.");
			token = strtok(NULL, delimiter);
			printf("Token: %s\n", token);

			strcpy(bufferOut, "From Server: Could not sign in.");

			for (int k = 0; k < numUsers; k++)
			{
				if (strcmp(allUsers[k].username, token) == 0)
				{
					token = strtok(NULL, delimiter);
					printf("Token: %s\n", token);

					if (strcmp(allUsers[k].password, token) == 0)
					{
						allUsers[k].isOnline = 1;
						allUsers[k].clientAddr.sin_family = clientAddr.sin_family;
						allUsers[k].clientAddr.sin_port = clientAddr.sin_port;
						allUsers[k].clientAddr.sin_addr.s_addr = clientAddr.sin_addr.s_addr;
						printf("%p", &clientAddr);
						strcpy(bufferOut, "From Server: Successfully signed in.");

					}
				}
			}
		}

		printf("Buffer: %s     Recieved from: %p\n", bufferOut, &clientAddr.sin_addr);
		sendto(socketFD, bufferOut, BUFFERSIZE, MSG_CONFIRM, (struct sockaddr*) &clientAddr, sizeof(clientAddr));
	}

	close(socketFD);
}