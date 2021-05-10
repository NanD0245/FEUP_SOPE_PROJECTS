#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "communication.h"

extern struct message m;


void initQueue(int max);

struct message* top();

bool isEmpty();

bool isFull();

int size();

void insert(struct message* data);

struct message* pop();

void freeQueue();

int getItemCount();

int getNumMessages();