#pragma once
#include <sys/times.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/times.h>
#include <time.h>

/**
 * @brief Stars the clock and saves the number of clock ticks per second.
 */
void init_clock();

/**
 * @brief Checks how much time a process took.
 */
bool check_time(char* argv[]);

/**
 * @brief Gets the remaining time after a process in seconds.
 * @return time remaining, in seconds.
 */
time_t get_remaining_time_secs(char * argv[]);

/**
 * @brief Gets the remaining time after a process in microseconds.
 * @return time remaining, in microseconds.
 */
suseconds_t get_remaining_time_micro(char * argv[]);