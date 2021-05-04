#include "communication.h"

struct message recieve_message(int argc, char* argv[]) {
    int public_fifo;
    struct message answer;
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
        else return answer;
    } 
    return answer;
}