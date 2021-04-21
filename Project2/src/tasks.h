#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int process_tasks(int argc, char* argv[]);

void * process_threads(void* arg);

int create_publicFIFO(int argc, char* argv[]);

int create_privateFIFO();
