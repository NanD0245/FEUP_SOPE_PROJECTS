#pragma once
#include <stdio.h>
#include "communication.h"

extern struct message m;

/**
 * @brief Processes the message sms and stores the task result to the struct
 * 
 * @param sms 
 */
void process_message(struct message* sms);