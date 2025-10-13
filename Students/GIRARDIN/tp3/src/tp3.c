#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#include "../include/hashtable.h"
#include "../include/mesh.h"
#include "../include/mesh_io.h"

 void timer_start(struct timeval *tv){gettimeofday(tv,NULL);}
 
 unsigned int timer_stop(const struct timeval *tv,const char *str){
    struct timeval now;
    gettimeofday(&now,NULL);

    unsigned int mus=1000000 * (now.tv_sec-tv->tv_sec);
    mus+=(now.tv_usec-tv->tv_usec);

    if(str[0]){
        printf("Timer%s: ",str);
        if(mus>=1000000){
            printf("%.3f s\n",(float)mus/1000000);
        }else{
            printf("%.3f ms\n",(float)mus/1000);
        }
    }
    return(mus);
 }
 
int main(int argc, char **argv){

    if(argc <= 1){
        printf("Missing filename; I need one in order to work :(\n");
        return EXIT_FAILURE;
    }

    char *filename = argv[1];
    struct Mesh m;

    int sucess = read_mesh_from_wavefront_file(&m, filename);

    if(sucess == -1){
        printf("Opening file failed ! That's bad :(\n");
        return EXIT_FAILURE;
    }

    struct timeval before;

    // timer_start(&before);
    // int *adj1 = build_adjacency_table1(&m);
    // timer_stop(&before, " of the first algorithm ");
    // free(adj1);

    timer_start(&before);
    int *adj2 = build_adjacency_table2(&m);
    timer_stop(&before, " of the second algorithm ");
    free(adj2);

    timer_start(&before);
    int *adj3 = build_adjacency_table3(&m);
    timer_stop(&before, " of the third algorithm ");
    free(adj3);

    return 0;
}