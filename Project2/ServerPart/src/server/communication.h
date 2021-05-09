#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include "tasks.h"
#include <sys/time.h>
#include "utils.h"
#include "register.h"
#include <sys/select.h>


/**
 * @brief struct that will contain the message.
 * RID - request id
 * PID - process id
 * TID - thread id
 * TSKLOAD - task load
 * TSKRES - task result
 */
struct message {
	int rid;	// request id
	pid_t pid;	// process id
	pthread_t tid;	// thread id
	int tskload;	// task load
	int tskres;	// task result
};

void update_message(struct message * sms);

int recieve_message(int argc,char* argv[], struct message * sms);

int insert_message(struct message * sms);

int send_message(struct message * sms);

int notify_finish();


