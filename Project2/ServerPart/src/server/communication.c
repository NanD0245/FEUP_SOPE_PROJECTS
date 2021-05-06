#include "communication.h"

extern pthread_mutex_t mutex;
extern sem_t full;
extern sem_t empty;

void update_message(struct message * sms) {
    sms->pid = getpid();
    sms->tid = pthread_self();
}

struct message recieve_message(int argc, char* argv[]) {
    int public_fifo;
    struct message answer;
    answer.tskload = -1;
    char name[2000];
    snprintf(name, 2000, "%s", argv[argc - 1]);

    while ((public_fifo = open(name, O_RDONLY | O_NONBLOCK)) < 0 && check_time(argc, argv)) {usleep(20000);};

    int sl;
    fd_set rfds;
    FD_ZERO(&rfds);
    FD_SET(public_fifo,&rfds);

    struct timeval tmv;

    if (get_remaining_time_secs(argv) >= 1) {
        tmv.tv_sec = get_remaining_time_secs(argv);
        tmv.tv_usec = 0;
    }
    else {
        tmv.tv_usec = get_remaining_time_micro(argv);
        tmv.tv_sec = 0;
    }

    if ((sl = select(public_fifo + 1, &rfds, NULL, NULL, &tmv)) == -1) {
        perror("ERROR - select");
    }
    else if (sl > 0) {
        if (read(public_fifo, &answer, sizeof(struct message)) < 0)
            perror("ERROR - read");
        else {
            register_message(&answer, "RECVD");
        }
    } 
    close(public_fifo);
    return answer;
}

int insert_message(struct message * sms) {

    if (sem_wait(&empty) != 0) {
        perror("ERROR - sem_wait");
        return -1;
    }

    pthread_mutex_lock(&mutex);

    insert(sms);

    pthread_mutex_unlock(&mutex);

    
    if (sem_post(&full) != 0) {
        perror("ERROR - sem_post");
        return -1;
    }

    return 0;
}

int send_message(struct message *sms) {
    char name[2000];
    snprintf(name, 2000, "/tmp/%d/%ld", sms->pid, sms->tid);

    int private_fifo;

    if ((private_fifo = open(name, O_WRONLY | O_NONBLOCK)) == -1) {
        register_message(sms, "FAILD");
    }
    else {

        if (write(private_fifo, sms, sizeof(struct message)) == -1)
            register_message(sms, "FAILD");
        else {
            if (sms->tskres == -1)
                register_message(sms, "2LATE");
            else
                register_message(sms, "TSKDN");
        }
    }

    close(private_fifo);

    return 0;
}


int notify_finish() {
    struct message sms;
    sms.tskres = -9999;

    insert_message(&sms);

    return 0;
}