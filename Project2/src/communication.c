#include "communication.h"

extern int ask_id;

struct message * generate_message(){
    struct message * sms = malloc(sizeof(struct message));

    //time_t t;

    

    sms->rid = ask_id;
    sms->pid = getpid();
    sms->tid = pthread_self();
    sms->tskload = rand()%9 + 1;
    sms->tskres = -1;

    return sms;
}

int send_message(int argc, char* argv[], struct message sms) {
    bool check;
    int public_fifo;
    while ((public_fifo = open(argv[argc - 1], O_WRONLY | O_NONBLOCK)) < 0) {
        if(!(check = check_time(argv))) break;
    }
    //write(public_fifo, &sms, sizeof(struct message));
    close(public_fifo);
    printf("inst ; %d ; %d ; %ld ; %d ; %d ; IWANT\n", sms.rid, sms.pid, sms.tid, sms.tskload, sms.tskres);
    return 0;
}

/*
struct message {
	int rid;	// request id
	pid_t pid;	// process id
	pthread_t tid;	// thread id
	int tskload;	// task load
	int tskres;	// task result
};
*/

int recieve_message(int argc, char* argv[], struct message sms) {
    bool check;
    int private_fifo;
    struct message answer;
    char * name = malloc(sizeof(char)*50);
    snprintf(name,50, "/tmp/%d.%ld", sms.pid, sms.tid);
    printf("%s\n", name);
    while ((private_fifo = open(name, O_RDONLY | O_NONBLOCK)) < 0 ) {
        if(!(check = check_time(argv))) { 
            printf("inst ; %d ; %d ; %ld ; %d ; %d ; GAVUP\n", sms.rid, sms.pid, sms.tid, sms.tskload, sms.tskres);
            break;
        }
    }
    read(private_fifo, &answer, sizeof(struct message));
    close(private_fifo);
    if (answer.tskres != -1) {
        printf("inst ; %d ; %d ; %ld ; %d ; %d ; GOTRS\n", answer.rid, answer.pid, answer.tid, answer.tskload, answer.tskres);
    }
    else {
        printf("inst ; %d ; %d ; %ld ; %d ; %d ; CLOSD\n", answer.rid, answer.pid, answer.tid, answer.tskload, answer.tskres);
    }
    return 0;
}
