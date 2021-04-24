#include "fifo.h"


int create_publicFIFO(int argc, char* argv[]){
    if (mkfifo(argv[argc-1], 0777) < 0) {
        perror("ERROR");
        return -1;
    }
    return 0;
}

int eliminate_publicFIFO(int argc, char* argv[]) {
    if (unlink(argv[argc - 1])){
        perror("ERROR");
        return -1;
    }
    return 0;
}

int create_privateFIFO(struct message **sms) 
{
    char * name = malloc(sizeof(char)*50);
    snprintf(name,50, "/tmp/%d.%ld", (*sms)->pid, (*sms)->tid);
    //printf("%s\n", name);
    if (mkfifo(name , 0666) < 0) {
        perror("ERROR");
        return -1;
    }
    return 0;
}

int eliminate_privateFIFO(struct message **sms)
{
    char * name = malloc(sizeof(char)*50);
    snprintf(name, 50, "/tmp/%d.%ld", (*sms)->pid, (*sms)->tid);
    if (unlink(name)){
        perror("ERROR");
        return -1;
    }
    return 0;
}