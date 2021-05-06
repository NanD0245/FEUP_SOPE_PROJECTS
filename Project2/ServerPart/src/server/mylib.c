#include "mylib.h"

void process_message(struct message * sms) {
    usleep(sms->tskload * 10e3);
    sms->tskres = sms->rid * 100;
}