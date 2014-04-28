CC=gcc
CFLAGS=-g -DTHREADED_SERVER
#CFLAGS=-g 
CLIENT_OBJS = \
	NMUSocket.o \
	fortuneClient.o 
SERVER_OBJS = \
	NMUSocket.o \
	fortuneServer.o 

LIBS= -lpthread
#LIBS=

all: fortuneClient fortuneServer

clean:
	rm -rf *.o *.dSYM fortuneServer fortuneClient

fortuneServer: $(SERVER_OBJS)
	$(CC) $(CFLAGS) $(SERVER_OBJS) $(LIBS) -o fortuneServer

fortuneClient: $(CLIENT_OBJS)
	$(CC) $(CFLAGS) $(CLIENT_OBJS) $(LIBS) -o fortuneClient

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
