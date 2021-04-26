#include "communication.h"

extern int ask_id;
extern int public_fifo;

struct message * generate_message(){
    struct message * sms = malloc(sizeof(struct message));

    sms->rid = ask_id;
    sms->pid = getpid();
    sms->tid = pthread_self();
    sms->tskload = rand()%9 + 1;
    sms->tskres = -1;

    return sms;
}

int send_message(int argc, char* argv[], struct message sms) {
    if (check_time(argv)) {
    printf("inst ; %d ; %d ; %ld ; %d ; %d ; IWANT\n", sms.rid, sms.pid, sms.tid, sms.tskload, sms.tskres);
    write(public_fifo, &sms, sizeof(struct message));
    }
    return 0;
}

int recieve_message(int argc, char* argv[], struct message sms) {
    int private_fifo;
    struct message answer; answer.rid = 0; answer.pid = 0;
    char * name = malloc(sizeof(char)*50);
    snprintf(name,50, "/tmp/%d.%ld", getpid(), pthread_self());
    printf("%s\n", name);
    if(!check_time(argv)) { 
        printf("inst ; %d ; %d ; %ld ; %d ; %d ; GAVUP\n", sms.rid, sms.pid, sms.tid, sms.tskload, sms.tskres);
        //close(private_fifo);
        return -1;
    }
    if (check_time(argv)) {
    while ((private_fifo = open(name, O_RDONLY)) < 0 && check_time(argv)) ;
    /*if(!check_time(argv)) { 
        printf("inst ; %d ; %d ; %ld ; %d ; %d ; GAVUP\n", sms.rid, sms.pid, sms.tid, sms.tskload, sms.tskres);
        close(private_fifo);
        return -1;
    }*/
    read(private_fifo, &answer, sizeof(struct message));
    close(private_fifo);
    
    if (answer.tskres != -1) {
        printf("inst ; %d ; %d ; %ld ; %d ; %d ; GOTRS\n", answer.rid, answer.pid, answer.tid, answer.tskload, answer.tskres);
    }
    else {
        printf("inst ; %d ; %d ; %ld ; %d ; %d ; CLOSD\n", answer.rid, answer.pid, answer.tid, answer.tskload, answer.tskres);
    }
    }
    return 0;
}
