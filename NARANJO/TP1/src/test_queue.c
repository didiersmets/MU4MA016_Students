#include <stdio.h>
#include <stdlib.h>

#include "../include/circular_buffer_queue.h"

typedef struct Queue Q;

int random_queue(int n){
	int l_max = 0;
	Q* q = queue_init(sizeof(int), n);
	for (int i; i < n; i++){
		int p = rand();
		if (p%2 == 0){
			queue_enqueue(q, &p);
		}
		else{
			void* dest = malloc(sizeof(int));
			queue_dequeue(q, dest);
			free(dest);
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
    random_queue(n);

    return 0;
}



