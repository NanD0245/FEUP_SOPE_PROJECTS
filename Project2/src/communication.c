#include "communication.h"
#include <pthread.h>
#include <unistd.h>

extern int ask_id;

void generate_message(struct message * sms){
    time_t t;

    /* Intializes random number generator */
    srand((unsigned) time(&t));

    sms->rid = ask_id;
    sms->pid = getpid();
    sms->tid = pthread_self();
    sms->tskload = rand()%10 + 1;
    sms->tskres = -1;
}
