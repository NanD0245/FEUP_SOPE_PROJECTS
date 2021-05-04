#pragma once
#include <stdio.h>

#include "utils.h"
#include "communication.h"

extern struct message m;

/**
 * @brief Struct that encapsulates the arguments that are passed to the threads.
 */
struct argCV {
    int argc;
    char **argv;
    struct message * sms;
};

int process_tasks(int argc, char* argv[]);

void* process_threads(void *arg);