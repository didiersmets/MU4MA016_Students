#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorting.h"

int main(void)
{
    int A[] = {10, 20, 50, 100, 200, 500, 1000};
    int A_antal = sizeof(A) / sizeof(A[0]);

    srand((unsigned)time(NULL));

    FILE *f = fopen("merge.txt", "w");
    if (!f)
    {
        perror("fopen");
        return 1;
    }

    for (int i = 0; i < A_antal; i++)
    {
        int N = A[i];
        int *data = malloc(N * sizeof(int));
        if (!data)
        {
            perror("malloc");
            return 1;
        }

        for (int j = 0; j < N; j++)
        {
            data[j] = rand();
        }

        clock_t start = clock();

        merge_sort(data, N);

        clock_t end = clock();
        double elapsed = (double)(end - start) / CLOCKS_PER_SEC;

        fprintf(f, "%d %f\n", N, elapsed);
        free(data);
    }

    fclose(f);
    system("gnuplot -persist -e \"set logscale x; set logscale y; plot 'merge.txt' using 1:2 with linespoints title 'Merge Sort'\"");

    return 0;
}