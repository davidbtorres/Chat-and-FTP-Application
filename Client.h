#ifndef CLIENT_H_
#define CLIENT_H_

void formatCommand(char option[], char username[], char password[]);
int authenticateCommand(socklen_t addressSize);

#endif