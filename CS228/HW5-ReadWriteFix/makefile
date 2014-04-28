CC=gcc
CFLAGS=-g
CLIENT_OBJS = \
	NMUSocket.o \
	fortuneClient.o 
SERVER_OBJS = \
	NMUSocket.o \
	fortuneServer.o 

all: fortuneClient fortuneServer

clean:
	rm -rf *.o *.dSYM fortuneServer fortuneClient

fortuneServer: $(SERVER_OBJS)
	$(CC) $(CFLAGS) $(SERVER_OBJS) -o fortuneServer

fortuneClient: $(CLIENT_OBJS)
	$(CC) $(CFLAGS) $(CLIENT_OBJS) -o fortuneClient

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
