#include <stdio.h>
#include <sys/times.h>
#include "utils.h"

clock_t start, end;
struct tms t;

int main(int argc, char* argv[], char* envp[]) {
    if (argc != 4) {
        printf("usage: c <-t nsecs> fifoname\n");
        return 0;
    }

    init_clock();

    while(check_time(argv)) ;

    return 0;
}