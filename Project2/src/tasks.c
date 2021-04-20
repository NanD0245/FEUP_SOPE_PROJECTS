#include "tasks.h"
#include <fcntl.h>
#include "utils.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>


int create_publicFIFO(int argc, char* argv[]){
    if (mkfifo(argv[argc-1], 0666) < 0) 
    {
        fprintf(stderr, "pipe error\n");
        return -1;
    }
    return 0;
}


int process_tasks(int argc, char* argv[]){

    while(check_time(argv)){
        
    }

    return 0;

}