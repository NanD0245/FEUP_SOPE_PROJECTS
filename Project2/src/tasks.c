#include "tasks.h"

int ask_id = 0;
pthread_mutex_t mut=PTHREAD_MUTEX_INITIALIZER;

int process_tasks(int argc, char* argv[]){
    int n_threads = 0;
    pthread_t * ids = (pthread_t *)malloc(sizeof(pthread_t));
    struct argCV args;
    args.argc = argc;
    args.argv = argv;

    while(check_time(argv)){

        ids = realloc(ids, (n_threads + 1)*sizeof(pthread_t));

        if(pthread_create(&ids[n_threads],NULL,process_threads,&args) != 0) {
			perror("pthread_create");
			exit(3);
		}
        n_threads++;
        usleep((rand() % 9 + 1) * 10e3);
    }

        printf("sai\n");
        printf("%d\n", ask_id);

    for (int i = 0; i < n_threads; i++) {
        printf("%d,\n",i);
        pthread_join(ids[i], NULL);
    }

        printf("passei\n");
    
    
    return 0;
}


void * process_threads(void* arg) {
    struct argCV *args = (struct argCV*)arg;
    if (check_time(args->argv)) {
    pthread_mutex_lock(&mut);
    //create

        struct message * sms = generate_message();
        ask_id++;
        create_privateFIFO(&sms);
        
        //TODO: server communication
        send_message(args->argc, args->argv, *sms);
        recieve_message(args->argc, args->argv, *sms);
        printf("entrei1\n");
        //eliminate
        eliminate_privateFIFO(&sms);
        printf("entrei2\n");
    
    pthread_mutex_unlock(&mut);
    }
    return NULL;
}