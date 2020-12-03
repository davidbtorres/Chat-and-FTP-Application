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

int main(void)
{
	int socketFD;
	struct sockaddr_in serverAddr, clientAddr;

	if (socketFD = socket(AF_INET, SOCK_DGRAM, 0) == -1)
	{
		perror("Socket creation failed");
		exit(EXIT_FAILURE)
	}
	else if (socketFD == 0)
	{
		printf("Socket creation successful");
	}

	memset(&serverAddr, 0, sizeof(serverAddr));
	memset(&serverAddr, 0, sizeof(serverAddr));

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	




}