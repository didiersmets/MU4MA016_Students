#include "sorting.h"
#include <stdio.h>
#include <sys/time.h> //For implementing a chrono (struct timeval and
#include <time.h>

void timer_start(struct timeval *tv){gettimeofday(tv,NULL);}

unsigned int timer_stop(const struct timeval *tv, const char *str){
    struct timeval now;
    gettimeofday(&now,NULL);
    unsigned int mus = 1000000 * (now.tv_sec - tv->tv_sec);
    mus += (now.tv_usec - tv->tv_usec);
    
    if(str[0]){
        printf("Timer%s:",str);
        if(mus >= 1000000){
            printf("%.3fs\n",(float)mus / 1000000);
        }else{
            printf("%.3fms\n",(float)mus / 1000);
        }
    }
    return(mus);
}