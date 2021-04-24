#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include "tasks.h"

/**
 * @brief struct that encapsulates what a message might be about.
 */
struct message {
	int rid;	// request id
	pid_t pid;	// process id
	pthread_t tid;	// thread id
	int tskload;	// task load
	int tskres;	// task result
};

/*
enum Oper = {IWANT, GOTRS, CLOSD, GAVUP};

send: IWANT - recieve: TSKDN -> ALL OK (RES) - print: GOTRS (recieved with success)
send: IWANT - recieve: 2LATE -> Service is closed (-1) - print: CLOSD (server reject order)
print: GAVUP (Times up)
*/

/**
 * @brief Generates a message.
 * 
 * @return struct message* - reference of the message created.
 */
struct message * generate_message();

int send_message(int argc, char* argv[], struct message sms);

int recieve_message(int argc, char* argv[], struct message sms);


