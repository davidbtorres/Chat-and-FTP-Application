/*
 * CS 484: Networking
 * Porject 2: Chat Application 
 * 
 * Group Member: 
 *  Omar Navarro 
 *  David Torres 
 *  Anaira Quezada
 *  Anissa Valenzuela
 * 
 * Purpose: 
 * Client function with UDP protocol
 * Client -> Server
 * Client.c executes after Server.c function
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
char bufferChat[BUFFERSIZE];
int socketFD;
struct sockaddr_in serverAddr;
socklen_t addressSize;
int chatFlag = 0;

const char delimiter[2] = ",";

int main(int argc, char *argv[])
{
	if(argc < 3)
	{
		printf("Invalid arguments, correct format is:\n./Client <IP> <PORT>\n");
		return 0;
	}

    /*
    * user is connected to the server
    */
    //char* server_IPAddress = argv[0]; 
    //int server_portNumber = htons(atoi(argv[2]));
	int isRunning = 1;
    char* token;

    char username[32];
    // char password[32];

    strcpy(username, "NOTSIGNEDIN");
    //printf("DEBUG: username at beginning of client.c: %s\n", username);

	socketFD = socket(AF_INET, SOCK_DGRAM, 0);

	if (socketFD < 0)
	{
		perror("Could not create socket.");
		exit(1);
	}//end of if

	memset(&serverAddr, 0, sizeof(serverAddr));

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(atoi(argv[2]));
  	serverAddr.sin_addr.s_addr = inet_addr(argv[1]);

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
    	while (!chatFlag)
    	{
    		continue;
    	}//end of while
    	chatFlag = 0;
    	strcpy(bufferOut, buffer);
        token = strtok(buffer, delimiter);
        // printf("%s\n", token);
        if(strcmp(token, "signin") == 0)
        {
        	token = strtok(NULL, delimiter);
        	strcpy(username, token);
        	printf("Signed to profile: %s\n", username);
        }//end of if

        else if(strcmp(token, "register") == 0)
        {
        	printf("%s\n", "From server: register successful");
        }//end of else if

        else if (strcmp(token, "signout") == 0)
        {
            printf("From server: Signout successful\n");
            break;
        }//end of else if

        else if (strcmp(token, "option0") == 0)
        {
    		//printf("%s\n", "option0 selected");
    		printf("%s\n", bufferOut);
        }//end of else if

        else if (strcmp(token, "option1") == 0)
        {
        	printf("%s\n", "Write your message:");
        	scanf("%s", bufferOut);
    		sendto(socketFD, bufferOut, BUFFERSIZE, MSG_CONFIRM, (struct sockaddr*) &serverAddr, sizeof(serverAddr));
        }//end of else if

        else if (strcmp(token, "refresh") == 0)
        {
        	printf("%s\n", "refreshed messages");
        }//end of else if

        else
        {
        	printf("ERROR: Command Failed\n");
        }//end of else



    }//end of while

    close(socketFD);
}//end of main 

/*
 * chatListener: 
 * Monitors the chat and will receive what is in the buffer
 * 
 */
void* chatListener()
{
	while (1)
	{
		recvfrom(socketFD, buffer, BUFFERSIZE, MSG_WAITALL, (struct sockaddr*) &serverAddr, &addressSize);
		chatFlag = 1;
		// signal to continue
		printf("%s\n", buffer);
	}//End of While
}//end of ChatListener

