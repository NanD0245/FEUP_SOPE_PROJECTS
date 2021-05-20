#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "communication.h"

extern struct message m;

/**
 * @brief 
 * 
 * @param max 
 */
void initQueue(int max);

/**
 * @brief Returns the element in front of the queue
 * 
 * @return struct message* 
 */
struct message* top();

/**
 * @brief Returns wheter the queue is empty or not
 * 
 * @return true 
 * @return false 
 */
bool isEmpty();


/**
 * @brief Returns wheter the queue is full or not
 * 
 * @return true 
 * @return false 
 */
bool isFull();

/**
 * @brief Used to get the size of the queue
 * 
 * @return int 
 */
int size();

/**
 * @brief Inserts another message into the queue( if the queue is not full) and updates variables
 * 
 * @param data 
 */
void insert(struct message* data);

/**
 * @brief Gets the next message and reduces the item count
 * 
 * @return struct message* 
 */

struct message* pop();
/**
 * @brief Deallocates the memory previously allocated for the queue
 */
void freeQueue();

/**
 * @brief Get the Item Count
 * 
 * @return int 
 */
int getItemCount();

/**
 * @brief Get the Number of Messages
 * 
 * @return int 
 */
int getNumMessages();