#ifndef SERVER_H_
#define SERVER_H_


struct user
{
	char username[32];
	char password[32];
	int isOnline;
	struct sockaddr_in clientAddr;
};

void reg(char password[], char username[]);
void signin(char password[], char username[], struct sockaddr_in* clientAddr);
void signout(char username[]);
void option0();

#endif