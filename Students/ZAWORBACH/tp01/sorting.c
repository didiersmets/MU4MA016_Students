#include <stdio.h> // for printf
#include <stdlib.h>
#include <time.h>
#include <string.h>

void print_array(float *arr, int size)
{
    for (int i = 0; i < size; i++) {
        printf("%.2f ", arr[i]);
    }
    printf("\n");
}


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
    int i=p;
    int left = p;  // keep track of left list
    int right = q+1;  // keep track of right list
    while (left <= q && right <= r)
    {
        if (from[left]<from[right])
        {
            to[i++]=from[left++];
        }
        else
        {
            to[i++]=from[right++];
        }
    }

    // above loop stops when one list exhausts. Copy the rest.
    while (left <= q) { to[i++] = from[left++]; }
    while (right <= r) { to[i++] = from[right++]; }

}

void merge_sort_subroutine(float *A, float *B, int p, int r)
{
    if (p < r)
    {
        int q = (p + r) / 2;
        merge_sort_subroutine(A, B, p, q);
        merge_sort_subroutine(A, B, q+1, r);
        merge(A, B, p, q, r);
        // Now A is sorted from p to r. Copy back to B.
        // debug print
        printf("A: ");
        print_array(A, r-p+1);
        printf("B:   ");
        print_array(B, r-p+1);
        printf("Merging p=%d, q=%d, r=%d\n", p, q, r);
        memcpy(&A[p], &B[p], sizeof(float)*(r-p+1));

    }
}
void merge_sort(float *A, int size)
{

    float *B = malloc (sizeof(float)*size);
    memcpy(B,A,sizeof(float)*size);

    merge_sort_subroutine(A, B, 0, size-1);

    free (B);
    
}

void generate_random_array(float *A, int size)
{
    for (int i = 0; i < size; i++)
    {
        A[i] = (float)(rand() % 1000);
    }
}



int main ()
{
    srand(time(NULL));
    int sizes[] = {10, 20, 50, 100, 200, 500, 1000};
    FILE *bubble_file = fopen("bubble_sort_data.txt", "w");
    FILE *insertion_file = fopen("insertion_sort_data.txt", "w");
    FILE *merge_file = fopen("merge_sort_data.txt", "w");

    for (int i = 0; i < sizeof(sizes)/sizeof(sizes[0]); i++)
    {
        int N = sizes[i];

        float *array1 = (float*)malloc(N * sizeof(float));
        float *array2 = (float*)malloc(N * sizeof(float));
        float *array3 = (float*)malloc(N * sizeof(float));

        generate_random_array(array1, N);
        memcpy(array2, array1, N * sizeof(float));
        memcpy(array3, array1, N * sizeof(float));

        clock_t start = clock();
        bubble_sort(array1, N);
        clock_t end = clock();
        double bubble_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // milliseconds
        fprintf(bubble_file, "%d\t%.6f\n", N, bubble_time);

        // Insertion Sort
        start = clock();
        insertion_sort(array2, N);
        end = clock();
        double insertion_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
        fprintf(insertion_file, "%d\t%.6f\n", N, insertion_time);

        // Merge Sort
        start = clock();
        merge_sort(array3, N);
        end = clock();
        double merge_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
        fprintf(merge_file, "%d\t%.6f\n", N, merge_time);

        free(array1);
        free(array2);
        free(array3);
    }

    fclose(bubble_file);
    fclose(insertion_file);
    fclose(merge_file);


    // Create gnuplot script
    FILE *gnuplot_script = fopen("plot_script.gp", "w");
    fprintf(gnuplot_script, "set terminal png size 800,600\n");
    fprintf(gnuplot_script, "set output 'sorting_comparison.png'\n");
    fprintf(gnuplot_script, "set logscale xy\n");
    fprintf(gnuplot_script, "set xlabel 'Array Size (N)'\n");
    fprintf(gnuplot_script, "set ylabel 'Execution Time (ms)'\n");
    fprintf(gnuplot_script, "set title 'Sorting Algorithm'\n");
    fprintf(gnuplot_script, "set grid\n");
    fprintf(gnuplot_script, "set key left top\n");
    fprintf(gnuplot_script, "plot 'bubble_sort_data.txt' using 1:2 with linespoints title 'Bubble Sort', \\\n");
    fprintf(gnuplot_script, "     'insertion_sort_data.txt' using 1:2 with linespoints title 'Insertion Sort', \\\n");
    fprintf(gnuplot_script, "     'merge_sort_data.txt' using 1:2 with linespoints title 'Merge Sort'\n");
    fclose(gnuplot_script);

    // Launch gnuplot
    system("gnuplot plot_script.gp");

    printf("Plot generated: sorting_comparison.png\n");

    return 0;


}
