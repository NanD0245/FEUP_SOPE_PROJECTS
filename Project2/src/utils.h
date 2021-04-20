#pragma once
#include <sys/times.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

/**
 * @brief Stars the clock and saves the number of clock ticks per second
 * 
 */
void init_clock();

/*
*/
bool check_time(char* argv[]);