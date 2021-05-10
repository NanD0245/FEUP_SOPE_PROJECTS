#pragma once
#include <stdio.h>
#include <semaphore.h>

#include "utils.h"
#include "communication.h"
#include "queue.h"
#include "lib.h"
#include "fifo.h"


/**
 * @brief Struct that encapsulates the arguments that are passed to the threads.
 */
struct argCV {
    int argc;
    char **argv;
    int id;
};

int process_tasks(int argc, char* argv[]);

void* process_threads(void *arg);

void* process_sc(void *arg);

