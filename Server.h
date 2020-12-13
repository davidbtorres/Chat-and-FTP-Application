#ifndef SERVER_H_
#define SERVER_H_

struct User
{
	char username[32];
	char password[32];
	int isOnline;
	struct sockaddr_in clientAddr;
};

struct Chat
{
	char username1[32];
	char username1[32];
	struct sockaddr_in userAddr1;
    struct sockaddr_in userAddr2;
};

void reg(char password[], char username[]);
void signin(char password[], char username[], struct sockaddr_in* clientAddr);
void signout(char username[]);
void option0();
int findUser(char username[]);
void option1(char user1[], char user2[]);
void chat(char username, char username[]);

#endif