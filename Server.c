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
char buffer[BUFFERSIZE];
char bufferOut[BUFFERSIZE];

int main(void)
{
	int socketFD;
	struct sockaddr_in serverAddr, clientAddr;
	socklen_t addressSize;
	int numBytes;
	
	char* token;
	const char delimiter[2] = ",";
	int isRunning = 1;

	socketFD = socket(AF_INET, SOCK_DGRAM, 0);

	if (socketFD < 0)
	{
		perror("Could not create socket.");
		exit(1);
	}

	memset(&serverAddr, 0, sizeof(serverAddr));
	memset(&clientAddr, 0, sizeof(clientAddr));

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	int bindStatus = bind(socketFD, (struct sockaddr*) &serverAddr, sizeof(serverAddr));
	if(bindStatus == -1)
	{
		perror("Bind failed");
	}

	addressSize = sizeof(clientAddr);

	while (isRunning)
	{			
		printf("%s", "Awaiting client...\n");

		numBytes = recvfrom(socketFD, buffer, BUFFERSIZE, MSG_WAITALL, (struct sockaddr*) &clientAddr, &addressSize);
		if(numBytes < 0)
		{
			perror("Unable to recieve message");
		}
		
		strcpy(bufferOut, buffer);

		token = strtok(buffer, delimiter);
		printf("Token: %s\n", token);

		if (strcmp(token, "0") == 0)
		{
			option0(bufferOut, sizeof(bufferOut));
		}

		else if (strcmp(token, "register") == 0)
		{
			reg(strtok(NULL, delimiter), strtok(NULL, delimiter));
		}

		else if (strcmp(token, "signin") == 0)
		{
			signin(strtok(NULL, delimiter), strtok(NULL, delimiter), (struct sockaddr_in*) &clientAddr);
		}

		else if (strcmp(token, "signout") == 0)
		{
			signout(strtok(NULL, delimiter));
		}

		printf("Buffer: %s Recieved from: %p\n", bufferOut, &clientAddr.sin_addr);
		sendto(socketFD, bufferOut, BUFFERSIZE, MSG_CONFIRM, (struct sockaddr*) &clientAddr, sizeof(clientAddr));
	}

	close(socketFD);
}

void option0()
{
	printf("%s\n", "Option 0 was recieved.");
	memset(bufferOut, '\0', sizeof(bufferOut));
	strcpy(bufferOut, "List of users online:\n");

	for (int i = 0; i < numUsers; i++)
	{
		if (allUsers[i].isOnline == 1)
		{
			strcat(bufferOut, allUsers[i].username);
			strcat(bufferOut, "\n");
		}
	}
}

void reg(char password[], char username[])
{
	printf("%s\n", "Register option executed.");
	printf("Username: %s    Password: %s\n", username, password);

	strcpy(allUsers[numUsers].username, username);
	strcpy(allUsers[numUsers].password, password);
	allUsers[numUsers].isOnline = 0;
	numUsers++;
	
	strcpy(bufferOut, "From Server: Successfully registered");
}

void signin(char password[], char username[], struct sockaddr_in* clientAddr)
{
	printf("%s\n", "Signin option executed.");
	strcpy(bufferOut, "From Server: Could not sign in.");

	for (int k = 0; k < numUsers; k++)
	{
		if (strcmp(allUsers[k].username, username) == 0)
		{
			if (strcmp(allUsers[k].password, password) == 0)
			{
				allUsers[k].isOnline = 1;
				allUsers[k].clientAddr.sin_family = clientAddr->sin_family;
				allUsers[k].clientAddr.sin_port = clientAddr->sin_port;
				allUsers[k].clientAddr.sin_addr.s_addr = clientAddr->sin_addr.s_addr;
				
				strcpy(bufferOut, "From Server: Successfully signed in.");
			}
		}
	}
}

void signout(char username[])
{
	printf("%s\n", "Signout option executed.");

	for (int k = 0; k < numUsers; k++)
	{
		if (strcmp(allUsers[k].username, username) == 0)
		{
			allUsers[k].isOnline = 0;
			strcpy(bufferOut, "signout");
			return;
		}
	}
}

int findUser(char username[])
{
	int result = -1;

	for (int i = 0; i < numUsers; i++)
	{
		if (strcmp(allUsers[i].username, username) == 0)
		{
			result = i;
			break;
		}
	}

	return result;
}