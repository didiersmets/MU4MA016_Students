#include <stdbool.h>
#include <sys/time.h>

bool is_sorted(int *arr, int n);  

void print_arr(int *arr, int length);

void bubble_sort(int *arr, int n);

void insertion_sort(int *arr, int n);

void merge_sort(int *T, int p, int r);

void merge(int* T, int p, int q, int r);

//Chrono : 
void timer_start(struct timeval *tv);

unsigned int timer_stop(const struct timeval *tv,const char *str);

