#include "tasks.h"

int ask_id = 0;
pthread_mutex_t mut=PTHREAD_MUTEX_INITIALIZER;

int process_tasks(int argc, char* argv[]){

    pthread_t * ids = (pthread_t *)malloc(sizeof(pthread_t));
    struct argCV args;
    args.argc = argc;
    args.argv = argv;

    while(check_time(argv)){

        ids = realloc(ids, (ask_id + 1)*sizeof(pthread_t));

        if(pthread_create(&ids[ask_id],NULL,process_threads,&args) != 0) {
			perror("pthread_create");
			exit(3);
		}
        usleep(1000);
    }

    for (int i = 0; i < ask_id; i++) {
        pthread_join(ids[i], NULL);
    }
    
    return 0;
}


void * process_threads(void* arg) {
    pthread_mutex_lock(&mut);

    //create
    struct argCV *args = (struct argCV*)arg;
    if (check_time(args->argv)) {
        struct message * sms = generate_message();
        ask_id++;
        create_privateFIFO(&sms);
        
        //TODO: server communication
        send_message(args->argc, args->argv, *sms);
        recieve_message(args->argc, args->argv, *sms);
        
        //eliminate
        eliminate_privateFIFO(&sms);
    }
    pthread_mutex_unlock(&mut);
    return NULL;
}