#include "queue.h"

struct message* *queue;
int max;
int front = 0;
int rear = -1;
int itemCount = 0;

void initQueue(int max_size) {
   queue = malloc( max_size * sizeof(struct message));
   max = max_size;
}

struct message* top() {
   return queue[front];
}

bool isEmpty() {
   return itemCount == 0;
}

bool isFull() {
   return itemCount == max;
}

int size() {
   return max;
}  

void insert(struct message* data) {

   if(!isFull()) {
	
      if(rear == max-1) {
         rear = -1;            
      }       

      queue[++rear] = data;
      itemCount++;
   }
}

struct message* pop() {
   struct message* data = queue[front++];
	
   if(front == max) {
      front = 0;
   }
	
   itemCount--;
   return data;  
}

void freeQueue() {
   free(queue);
}