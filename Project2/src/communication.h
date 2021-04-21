#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "tasks.h"



struct message {
	int rid;	// request id
	pid_t pid;	// process id
	pthread_t tid;	// thread id
	int tskload;	// task load
	int tskres;	// task result
};

//enum Oper = {IWANT, GOTRS, CLOSD, GAVUP};

void generate_message(struct message * sms);


