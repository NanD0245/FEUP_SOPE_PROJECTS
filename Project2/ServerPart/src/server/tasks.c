#include "tasks.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

sem_t empty;
sem_t full;

int process_tasks(int argc, char* argv[]) {

    initQueue((argc == 4) ? 10 : atoi(argv[4]));

    pthread_t sc;  

    pthread_create(&sc, NULL, process_sc, NULL);


    if (sem_init(&empty, 0, size()) != 0 || sem_init(&full, 0, 0)) {
        perror("ERROR - sem_init");
        return 1;
    }

    int n_threads = 0;
    pthread_t * ids = (pthread_t *)malloc(sizeof(pthread_t));

    //struct message* all_messages = malloc(sizeof(struct message));

    while (check_time(argc, argv)) {
        
        struct argCV * args = malloc(sizeof(struct argCV));
        args->argc = argc;
        args->argv = argv;

        struct message * sms = malloc(sizeof(struct message));
        if (recieve_message(argc, argv, sms) != 0) {
            continue;
        }
        
        args->sms = sms;

        ids = realloc(ids, (n_threads + 1)*sizeof(pthread_t));

        if(pthread_create(&ids[n_threads],NULL,process_threads,(void*)args) != 0) {
			perror("ERROR - pthread_create");
			exit(3);
		}
        n_threads++;
    }

    notify_finish();

    for (int i = 0; i < n_threads; i++) {
        pthread_join(ids[i], NULL);
    }

    sem_destroy(&empty);
    sem_destroy(&full);

    //return 0;

    pthread_join(sc, NULL);

    freeQueue();

    free(ids);

    return 0;
}

void* process_threads(void *arg) {
    struct argCV args = *(struct argCV*)arg;
    free(arg);

    if (check_time(args.argc, args.argv)) {
        process_message(args.sms);

        register_message(args.sms, "TSKEX");

        insert_message(args.sms);

        printf("passei - insert_message\n");
    }

    return NULL;
}

void * process_sc(void* arg) { 
    struct message* sms;

    int val;

    sem_getvalue(&full, &val);
    printf("sem_full: %d\n", val);
    sem_getvalue(&empty, &val);
    printf("sem_empty: %d\n", val);

    while (1) {
        if (sem_wait(&full) != 0) { continue; }

        pthread_mutex_lock(&mutex);
        sms = pop();
        pthread_mutex_unlock(&mutex);

        if (sem_post(&empty) != 0) { perror("ERROR - sem_post"); }

        if (sms->tskres == -9999) { break; }

        send_message(sms);
    }
    return NULL;
 }
