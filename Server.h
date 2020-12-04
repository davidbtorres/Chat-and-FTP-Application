#ifndef SERVER_H_
#define SERVER_H_

struct user
{
	char username[32];
	char password[32];
	int isOnline = 0;
	struct sockaddr_in clientAddr;
}

void serverGreeting();
int signup(char* username, char* password);
int signin(char* username, char* password);
void logout(char* username);
void option0(char* username); // List Users
int option1(char* ...); // Create new chat with specified users
void option2(char* fielname, char* ...); // File transfer

#endif