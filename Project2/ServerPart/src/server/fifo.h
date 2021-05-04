#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "string.h"
#include "utils.h"


/**
 * @brief Creates the publicFIFO.
 * @return Whether it was successful or not. 
 */
int create_publicFIFO(int argc, char* argv[]);

int unlink_publicFIFO(int argc, char* argv[]);