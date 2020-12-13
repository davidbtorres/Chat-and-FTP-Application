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
char bufferOut[BUFFERSIZE];
int socketFD;
struct sockaddr_in serverAddr;

const char delimiter[2] = ",";

int main(void)
{
	socklen_t addressSize;
	int isRunning = 1;
    char* token;

    char username[32];
    char password[32];

    strcpy(username, "nsi");
    printf("DEBUG: username at beginning of client.c: %s\n", username);

	socketFD = socket(AF_INET, SOCK_DGRAM, 0);

	if (socketFD < 0)
	{
		perror("Could not create socket.");
		exit(1);
	}

	memset(&serverAddr, 0, sizeof(serverAddr));

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
  	serverAddr.sin_addr.s_addr = inet_addr("192.168.1.3");

  	/*
  	int registerStatus = 1;
  	char ans[32];
  	while (registerStatus)
  	{
  		strcpy(bufferOut, "nsi,");
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
	  				registerStatus = 1;
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
	*/

	/*
	Precondition: The user is already signed in.
	Functionality: This loop allows the user to access commands from the server. 
	*/
    while (isRunning)
    {
    	printf("DEBUG: username at beginning of main loop: %s\n", username);
    	printf("%s", "Command: ");
    	strcpy(bufferOut, username);
    	printf("DEBUG: bufferOut after setting it to username: %s\n", bufferOut);
    	strcat(bufferOut, delimiter);
    	char ye[32];
    	scanf("%s", ye);
    	strcat(bufferOut, ye);
    	printf("DEBUG: buffer at before its sent to server: %s\n", bufferOut);
    	sendto(socketFD, bufferOut, BUFFERSIZE, MSG_CONFIRM, (struct sockaddr*) &serverAddr, sizeof(serverAddr));
    	printf("%s\n", "Message sent");
    	addressSize = sizeof(serverAddr);
    	recvfrom(socketFD, buffer, BUFFERSIZE, MSG_WAITALL, (struct sockaddr*) &serverAddr, &addressSize);
        token = strtok(buffer, delimiter);

        if (strcmp(token, "signout") == 0)
        {
            printf("From server: Signout successful\n");
            break;
        }
        else if (strcmp(token, "chat") == 0)
        {
        	token = strtok(NULL, delimiter);
        	if (strcmp(token, "1") == 0)
        	{
        		// create the thread from this thread send to server
        		// invoke new terminal
        		// invoke chat function (send command to server)

        	}
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
	strcat(bufferOut, option);
	strcat(bufferOut, delimiter);
	strcat(bufferOut, username);
	strcat(bufferOut, delimiter);
	strcat(bufferOut, password);
	strcat(bufferOut, delimiter);
}

int authenticateCommand(socklen_t addressSize)
{
	printf("%s\n", "Authenticating...");
	sendto(socketFD, bufferOut, BUFFERSIZE, MSG_CONFIRM, (struct sockaddr*) &serverAddr, addressSize);
	recvfrom(socketFD, buffer, BUFFERSIZE, MSG_WAITALL, (struct sockaddr*) &serverAddr, &addressSize);
	return (strcmp(buffer, "1") == 0);
}