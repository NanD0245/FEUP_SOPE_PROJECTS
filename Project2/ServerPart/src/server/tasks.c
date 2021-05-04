#include "tasks.h"

int process_tasks(int argc, char* argv[]) {

    int n_threads = 0;
    pthread_t * ids = (pthread_t *)malloc(sizeof(pthread_t));
    struct argCV args;
    args.argc = argc;
    args.argv = argv;

    while (check_time(argc, argv)) {
        struct message sms = recieve_message(argc, argv);
        args.sms = &sms;

        ids = realloc(ids, (n_threads + 1)*sizeof(pthread_t));

        if(pthread_create(&ids[n_threads],NULL,process_threads,&args) != 0) {
			perror("pthread_create");
			exit(3);
		}
        n_threads++;

    }

    return 0;
}

void* process_threads(void *arg) {
    return NULL;
}