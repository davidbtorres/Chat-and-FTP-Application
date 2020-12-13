OBJS	= Server.o Client.o
OUT	= Server, Client

OBJS0	= Server.o
SOURCE0	= Server.c
HEADER0	= 
OUT0	= Server

OBJS1	= Client.o
SOURCE1	= Client.c
HEADER1	= 
OUT1	= Client

CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: Server Client

Server: $(OBJS0) $(LFLAGS)
	$(CC) -g $(OBJS0) -o $(OUT0)

Client: $(OBJS1) $(LFLAGS)
	$(CC) -pthread -g $(OBJS1) -o $(OUT1)

Server.o: Server.c
	$(CC) $(FLAGS) Server.c

Client.o: Client.c
	$(CC) $(FLAGS) Client.c 


clean:
	rm -f $(OBJS) $(OUT0) $(OBJS1) $(OUT1)