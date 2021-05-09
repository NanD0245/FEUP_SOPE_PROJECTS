#include "tasks.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t output_mutex = PTHREAD_MUTEX_INITIALIZER;

sem_t empty;
sem_t full;

int public_fifo;

struct message* all_messages;

int process_tasks(int argc, char* argv[]) {
    
    initQueue((argc == 4) ? 10 : atoi(argv[4]));

    char name[2000];
    snprintf(name, 2000, "%s", argv[argc - 1]);

    if ((public_fifo = open(name, O_RDONLY | O_NONBLOCK)) < 0 ) {
        perror("ERROR - open");
        return 1;
    }

    if (sem_init(&empty, 0, size()) != 0 || sem_init(&full, 0, 0)) {
        perror("ERROR - sem_init");
        return 1;
    }

    pthread_t sc;  

    pthread_create(&sc, NULL, process_sc, NULL);

    int n_threads = 0, n_messages = 0;
    pthread_t * ids = malloc(sizeof(pthread_t));

    all_messages = malloc(1000 * sizeof(struct message));

    while (check_time(argc, argv)) {
        
        struct argCV * args = malloc(sizeof(struct argCV));
        args->argc = argc;
        args->argv = argv;
        
        //pthread_mutex_lock(&output_mutex);
        //all_messages = realloc(all_messages, (n_messages + 1) * sizeof(struct message));
        //pthread_mutex_unlock(&output_mutex);


        if (recieve_message(argc, argv, &all_messages[n_messages]) != 0) {
            continue;
        }

        args->id = n_messages;

        ids = realloc(ids, (n_threads + 1)*sizeof(pthread_t));

        if(pthread_create(&ids[n_threads],NULL,process_threads,(void*)args) != 0) {
			perror("ERROR - pthread_create");
			exit(3);
		}
        n_threads++;
        n_messages++;
    }

    notify_finish();
    
    pthread_join(sc, NULL);
    
    for (int i = 0; i < n_threads; i++) {
        pthread_join(ids[i], NULL);
    }
    
    sem_destroy(&empty);
    sem_destroy(&full);

    close(public_fifo);
    
    free(all_messages);

    freeQueue();

    free(ids);

    return 0;
}

void* process_threads(void *arg) {

    register_message(&all_messages[((struct argCV*)arg)->id], "CHECK_ARG");

    struct argCV args = *(struct argCV*)arg;

    free(arg);

    if (check_time(args.argc, args.argv)) {
        pthread_mutex_lock(&output_mutex);

        process_message(&(all_messages[args.id]));

        pthread_mutex_unlock(&output_mutex);

        register_message(&all_messages[args.id], "TSKEX");

        insert_message(&all_messages[args.id]);
    }

    return NULL;
}

void * process_sc(void* arg) { 
    struct message* sms;

    while (1) {
        if (sem_wait(&full) != 0) { continue; }

        //pthread_mutex_lock(&output_mutex);

        pthread_mutex_lock(&mutex);
        sms = pop();
        pthread_mutex_unlock(&mutex);

        if (sem_post(&empty) != 0) { perror("ERROR - sem_post"); }

        if (sms->tskres == -9999) { break; }

        send_message(sms);
        //pthread_mutex_unlock(&output_mutex);
    }
    while(!isEmpty()) {
        pthread_mutex_lock(&mutex);
        printf("size : %d\n", getItemCount());
        sms = pop();
        send_message(sms);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
 }
