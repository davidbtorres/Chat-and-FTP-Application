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
#include "Client.h"

#define PORT 5000
#define BUFFERSIZE 1024

char buffer[BUFFERSIZE];
int socketFD;
struct sockaddr_in serverAddr;

int main(void)
{
	socklen_t addressSize;
	int isRunning = 1;
    char* token;
    const char delimiter[2] = ",";

    char username[32];
    char password[32];

	socketFD = socket(AF_INET, SOCK_DGRAM, 0);

	if (socketFD < 0)
	{
		perror("Could not create socket.");
		exit(1);
	}

	memset(&serverAddr, 0, sizeof(serverAddr));

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
  	serverAddr.sin_addr.s_addr = inet_addr("192.168.1.9");

  	int registerStatus = 1;
  	char ans[32];
  	while (registerStatus)
  	{
	  	printf("%s\n", "Have you registered an account? [y/n]");
	  	scanf("%s", ans);

  		registerStatus = 0;
	  	if (strcmp(ans, "y") == 0)
	  	{
	  		formatCommand("signin", username, password);
	  		if (authenticateCommand(sizeof(serverAddr)))
	  		{
	  			printf("%s\n", "Sign in successful");
	  		}
	  		else
	  		{
	  			printf("%s\n", "ERROR: Sign in failed");
	  		}
	  	}
	  	else if (strcmp(ans, "n") == 0)
	  	{
	  		formatCommand("register", username, password);
	  		if (authenticateCommand(sizeof(serverAddr)))
	  		{
	  			printf("%s\n", "Successfully registered account\n\nPlease sign in");
	  			formatCommand("signin", username, password);
	  			if (authenticateCommand(sizeof(serverAddr)))
	  			{
	  				printf("%s\n", "Sign in successful");
	  			}
	  			else
	  			{
	  				printf("%s\n", "ERROR: Sign in failed");
	  			}
	  		}
	  		else
	  		{
	  			printf("%s\n", "ERROR: Failed to register account");
	  			registerStatus = 1;
	  		}
	  	}
	  	else
	  	{
	  		printf("%s\n", "ERROR: Invalid input");
	  		registerStatus = 1;
	  	}
	}

    while (isRunning)
    {
    	printf("Enter message\n");
    	scanf("%s", buffer);
    	sendto(socketFD, buffer, BUFFERSIZE, MSG_CONFIRM, (struct sockaddr*) &serverAddr, sizeof(serverAddr));
    	printf("Message sent\n");
    	addressSize = sizeof(serverAddr);
    	recvfrom(socketFD, buffer, BUFFERSIZE, MSG_WAITALL, (struct sockaddr*) &serverAddr, &addressSize);
        token = strtok(buffer, delimiter);

        if (strcmp(token, "signout") == 0)
        {

            printf("From server: Signout successful\n");
            break;
        }

    	printf("%s\n", buffer);
    }

    close(socketFD);
}

void formatCommand(char option[], char username[], char password[])
{
	printf("%s", "Please enter a username: ");
	scanf("%s", username);
	printf("\n%s", "Please enter a password: ");
	scanf("%s", password);
	printf("\n");
	strcpy(buffer, option);
	strcat(buffer, ",");
	strcat(buffer, username);
	strcat(buffer, ",");
	strcat(buffer, password);
}

int authenticateCommand(socklen_t addressSize)
{
	printf("%s\n", "Authenticating...");
	sendto(socketFD, buffer, BUFFERSIZE, MSG_CONFIRM, (struct sockaddr*) &serverAddr, addressSize);
	recvfrom(socketFD, buffer, BUFFERSIZE, MSG_WAITALL, (struct sockaddr*) &serverAddr, &addressSize);
	return (strcmp(buffer, "1") == 0);
}