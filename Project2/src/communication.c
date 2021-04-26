#include "communication.h"

extern int ask_id;
extern int public_fifo;

struct message * generate_message(int id){
    struct message * sms = malloc(sizeof(struct message));

    sms->rid = id;
    sms->pid = getpid();
    sms->tid = pthread_self();
    sms->tskload = rand()%9 + 1;
    sms->tskres = -1;

    return sms;
}

int send_message(int argc, char* argv[], struct message sms) {
    if (check_time(argv)) {
        printf("%ld ; %d ; %d ; %ld ; %d ; %d ; IWANT\n", time(NULL), sms.rid, sms.pid, sms.tid, sms.tskload, sms.tskres);
        write(public_fifo, &sms, sizeof(struct message));
    }
    return 0;
}

int recieve_message(int argc, char* argv[], struct message sms) {
    int private_fifo;
    struct message answer; answer.rid = 0; answer.pid = 0;
    char * name = malloc(sizeof(char)*50);
    snprintf(name,50, "/tmp/%d.%ld", getpid(), pthread_self());

    while ((private_fifo = open(name, O_RDONLY | O_NONBLOCK)) < 0 && check_time(argv)) ;

    int sl;
    fd_set rfds;
    FD_ZERO(&rfds);
    FD_SET(private_fifo,&rfds);

    struct timeval tmv;

    if (get_remaining_time_secs(argv) >= 1) {
        tmv.tv_sec = get_remaining_time_secs(argv);
        tmv.tv_usec = 0;
    }
    else {
        tmv.tv_usec = get_remaining_time_micro(argv);
        tmv.tv_sec = 0;
    }

    if ((sl = select(private_fifo + 1, &rfds, NULL, NULL, &tmv)) == -1) {
        perror("ERROR - select");
    }
    else if (sl > 0) {
        if (read(private_fifo, &answer, sizeof(struct message)) < 0)
            perror("ERROR - read");
    
        if (answer.tskres != -1) {
            printf("%ld ; %d ; %d ; %ld ; %d ; %d ; GOTRS\n", time(NULL), answer.rid, sms.pid, sms.tid, answer.tskload, answer.tskres);
        }
        else {
            printf("%ld ; %d ; %d ; %ld ; %d ; %d ; CLOSD\n", time(NULL), answer.rid, sms.pid, sms.tid, answer.tskload, answer.tskres);
        }
    }
    else if (sl == 0) {
        printf("%ld ; %d ; %d ; %ld ; %d ; %d ; GAVUP\n", time(NULL), sms.rid, sms.pid, sms.tid, sms.tskload, sms.tskres);
    }
    close(private_fifo);

    return 0;
}
