#include <stdio.h> // for printf
#include <stdlib.h>
#include <time.h>
#include <string.h>

void bubble_sort (float *A, int size)
{
    for (int i=1; i<size;i++)
    {
        for (int j=0; j<size-i;j++)
        {
            if (A[j]>A[j+1])
            {
                float tmp = A[j];
                A[j] = A[j+1];
                A[j+1] = tmp;

            }
        }
    }
}

void insertion_sort (float *A, int size)
{
    for (int i = 1; i<size;i++)
    {
        for (int j=i;j>0&&A[j]<A[j-1];j--)
        {
                float tmp = A[j];
                A[j] = A[j-1];
                A[j-1] = tmp;

        }
    }
}


void merge (float *from, float *to, int p, int q, int r)
{
    int i=0;
    while (p < q && q < r)
    {
        if (from[p]<from[q])
        {
            to[i++]=from[p++];
        }
        else
        {
            to[i++]=from[q++];
        }
    }

    // above loop stops when one list exhausts. Copy the rest.
    while (p<q) {to[i++]=from[p++];}
    while (q<r) {to[i++]=from[q++];}

}

void merge_sort_subroutine(float *A, float *B, int p, int r)
{
    if (p < r)
    {
        int q = (p + r) / 2;
        merge_sort_subroutine(A, B, p, q);
        merge_sort_subroutine(A, B, q+1, r);
        merge(A, B, p, q, r);
    }

}

void merge_sort(float *A, int size)
{

    float *B = malloc (sizeof(float)*size);
    memcpy(B,A,sizeof(float)*size);

    merge_sort_subroutine(A, B, 0, size-1);

    free (B);
    
}

void generate_random_array (int *A, int size)
{
    // Generate random array with values 1-1000
    for (int i=0; i<size;i++)
    {
        A[i] = rand()%1000 ;
    }
}

int main ()
{
    int sizes[] = {10, 20, 50, 100, 200, 500, 1000};
    srand(time(NULL));

    FILE *bubble_file = fopen("bubble_sort_data.txt", "w");
    FILE *insertion_file = fopen("insertion_sort_data", "w");
    FILE *merge_file = fopen("insertion_sort_data", "w");


    for (int i=0; i<sizeof(sizes)/sizeof(int);i++)
    {
        int N = sizes[i];
        
        // Allocate arrays
        float *array1 = (float*)malloc(N * sizeof(float));
        float *array2 = (float*)malloc(N * sizeof(float));
        float *array3 = (float*)malloc(N * sizeof(float));


        generate_random_array(array1, N);

        memcpy(array2, array1, N * sizeof(float));

        clock_t start = clock();
        bubble_sort(array1, N);
        clock_t end = clock();
        fprintf(bubble_file, "%d\t%.3f\n", N, (double)(end - start));

        clock_t start = clock();
        insertion_sort(array2, N);
        clock_t end = clock();
        fprintf(insertion_file, "%d\t%.3f\n", N, (double)(end - start));

        clock_t start = clock();
        merge_sort(array3, N);
        clock_t end = clock();
        fprintf(merge_file, "%d\t%.3f\n", N, (double)(end - start));

        fprintf(bubble_file, "%d\t%.3f\n")

        free (array1);
        free (array2);
        free (array3);



    }
}

