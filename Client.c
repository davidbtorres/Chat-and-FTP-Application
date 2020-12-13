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
#include <pthread.h>
#include "Client.h"

#define PORT 5000
#define BUFFERSIZE 1024

char buffer[BUFFERSIZE];
char bufferOut[BUFFERSIZE];
int socketFD;
struct sockaddr_in serverAddr;
socklen_t addressSize;

const char delimiter[2] = ",";

int main(void)
{
	int isRunning = 1;
    char* token;

    char username[32];
    char password[32];

    strcpy(username, "NOTSIGNEDIN");
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
  	serverAddr.sin_addr.s_addr = inet_addr("10.0.0.40");

  	pthread_t thread;
	pthread_create(&thread, NULL, chatListener, (void*)NULL);

	/*
	Precondition: The user is already signed in.
	Functionality: This loop allows the user to access commands from the server. 
	*/
    while (isRunning)
    {
    	printf("%s", "Command: ");
    	strcpy(bufferOut, username);
    	strcat(bufferOut, delimiter);
    	char nextCommand[32];
    	scanf("%s", nextCommand);
    	strcat(bufferOut, nextCommand);
    	sendto(socketFD, bufferOut, BUFFERSIZE, MSG_CONFIRM, (struct sockaddr*) &serverAddr, sizeof(serverAddr));
    	printf("%s\n", "Message sent");
    	addressSize = sizeof(serverAddr);
    	recvfrom(socketFD, buffer, BUFFERSIZE, MSG_WAITALL, (struct sockaddr*) &serverAddr, &addressSize);
        token = strtok(buffer, delimiter);
        if(strcmp(token, "signin") == 0)
        {
        	token = strtok(NULL, delimiter);
        	strcpy(username, token);
        	printf("Signed to profile: %s\n", username);
        }

        else if (strcmp(token, "signout") == 0)
        {
            printf("From server: Signout successful\n");
            break;
        }

        else if (strcmp(token, "option1") == 0)
        {
        	printf("%s\n", "Write your message:");
        	scanf("%s", bufferOut);
    		sendto(socketFD, bufferOut, BUFFERSIZE, MSG_CONFIRM, (struct sockaddr*) &serverAddr, sizeof(serverAddr));
    		recvfrom(socketFD, buffer, BUFFERSIZE, MSG_WAITALL, (struct sockaddr*) &serverAddr, &addressSize);
        }
        else
        {
        	printf("ERROR: Command Failed");
        }

    	printf("%s\n", buffer);
    }

    close(socketFD);
}

void* chatListener()
{
	while (1)
	{
		printf("%s\n", "I LISTEN");
		recvfrom(socketFD, buffer, BUFFERSIZE, MSG_WAITALL, (struct sockaddr*) &serverAddr, &addressSize);
		// signal to continue
		printf("%s\n", buffer);
	}
}