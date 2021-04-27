all: s

s: server/server.c
	gcc -Wall -o s server/server.c -pthread #-DDELAY=0

clean:
	rm -f s