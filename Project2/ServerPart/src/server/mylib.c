#include "mylib.h"

void process_message(struct message* sms) {
    usleep(sms->tskload * 10e3);
    sms->tskres = (int)sms->rid * 100;
}