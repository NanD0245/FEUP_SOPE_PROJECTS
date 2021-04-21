#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


static int ask_id = 0;

struct message {
	int rid;	// request id
	pid_t pid;	// process id
	pthread_t tid;	// thread id
	int tskload;	// task load
	int tskres;	// task result
};

void generate_message(struct message * sms);


