#all: s

s: server/server.c server/utils.c server/fifo.c server/tasks.c server/communication.c server/queue.c server/mylib.c server/register.c
	gcc -Wall -o s server/server.c server/utils.c server/fifo.c server/tasks.c server/communication.c server/queue.c server/mylib.c server/register.c -pthread #-DDELAY=0

clean:
	rm -f s