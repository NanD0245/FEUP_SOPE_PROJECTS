#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "tasks.h"
#include <fcntl.h>
#include "string.h"
#include "utils.h"
#include "communication.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "fifo.h"

extern struct message m;

struct argCV {
    int argc;
    char **argv;
    int id;
};

/**
 * @brief processes a task. 
 * @return Indication that it was successful.
 */
int process_tasks(int argc, char* argv[]);

/**
 * @brief Processes a thread passed on as argument.
 * @return void* 
 */
void * process_threads(void* arg);