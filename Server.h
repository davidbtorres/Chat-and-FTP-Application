#ifndef SERVER_H_
#define SERVER_H_


struct user
{
	char username[32];
	char password[32];
	int isOnline;
	struct sockaddr_in clientAddr;
};

void serverGreeting();
int userOnline(struct sockaddr_in clientAddr);
void reg(char password[], char username[]);
void signin(char password[], char username[], struct sockaddr_in* clientAddr);
void logout(char* username);
void option0();
int option1(char*, ...); // Create new chat with specified users
void option2(char* fielname, char*, ...); // File transfer

#endif