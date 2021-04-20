#include "utils.h"

extern clock_t start, end;
extern struct tms t;

void init_clock(){
    start = times(&t);
}

bool check_time(char* argv[]) {
    char* ptr;
    int long ticks = sysconf(_SC_CLK_TCK);
    end = times(&t);
    if (strtod(argv[2], &ptr) <= (double)(end - start) / ticks) return false;
    return true;
}