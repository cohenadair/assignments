CC=gcc
CFLAGS=-g

all: fortuneClient fortuneServer

clean:
	rm -rf *.o fortuneServer fortuneClient

fortuneServer: fortuneServer.c
	$(CC) $(CFLAGS) fortuneServer.c -o fortuneServer

fortuneClient: fortuneClient.c
	$(CC) $(CFLAGS) fortuneClient.c -o fortuneClient