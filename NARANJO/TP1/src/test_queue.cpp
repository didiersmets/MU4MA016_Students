#include <stdio.h>
#include <stdlib.h>

#include "../src/circular_buffer_queue2.h"


typedef struct Queue<int>* Q;

int random_queue(int n){
	size_t l_max = 0;
	Q q = queue_init<int>(n);
	for (int i = 0; i < n; i++){
		int p = rand();
		if (p%2 == 0){
			queue_enqueue<int>(q, p);
		}
		else{
			queue_dequeue<int>(q);
		}
		if (queue_length(q) > l_max){
			l_max = queue_length(q);
		}
	}
	return l_max;
}

int main() {
    int n;

    // Prompt user to enter number of successive random integers
    printf("Enter the number of successive random integers to be picked: ");
    scanf("%d", &n);

    // Print Pascal's triangle
    printf("%d \n" , random_queue(n));

    return 0;
}
