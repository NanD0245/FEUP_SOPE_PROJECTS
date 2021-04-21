#include "tasks.h"
#include <fcntl.h>
#include "string.h"
#include "utils.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int ask_id = 0;
pthread_mutex_t mut=PTHREAD_MUTEX_INITIALIZER;

int create_publicFIFO(int argc, char* argv[]){
    if (mkfifo(argv[argc-1], 0666) < 0) 
    {
        fprintf(stderr, "pipe error\n");
        return -1;
    }
    return 0;
}

int create_privateFIFO() {
    return 0;
}


int process_tasks(int argc, char* argv[]){

    pthread_t ptid;

    while(check_time(argv)){
        if(pthread_create(&ptid,NULL,process_threads,NULL) != 0) {
			perror("pthread_create");
			exit(3);
		}
        ask_id++;
    }

    return 0;

}


void * process_threads(void* arg) {
    pthread_mutex_lock(&mut);
    pthread_exit(NULL);
    pthread_mutex_unlock(&mut);
}