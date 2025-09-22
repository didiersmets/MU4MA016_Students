#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void bubble_sort(int *array, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (array[j] > array[j + 1])
            {
                int temp = array[j + 1];
                array[j + 1] = array[j];
                array[j] = temp;
            }
        }
    }
    return;
}

int main()
{
    int test_array[] = {64, 34, 25, 12, 22, 11, 90};
    int test_size = sizeof(test_array) / sizeof(test_array[0]);

    printf("Original array: ");
    for (int i = 0; i < test_size; i++)
    {
        printf("%d ", test_array[i]);
    }
    printf("\n");

    bubble_sort(test_array, test_size);

    printf("Sorted array:   ");
    for (int i = 0; i < test_size; i++)
    {
        printf("%d ", test_array[i]);
    }
    printf("\n\n");

    int sizes[] = {10, 20, 50, 100, 200, 500, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000, 5500, 6000, 6500, 7000, 7500, 8000, 8500, 9000, 9500, 10000, 12000, 14000, 16000, 18000, 20000, 22000, 24000, 26000, 28000, 30000, 35000, 40000, 45000, 50000, 55000, 60000, 65000, 70000, 75000, 80000, 85000, 90000, 95000, 100000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    FILE *f = fopen("bubble_sort_time_data.txt", "w");
    if (!f)
    {
        perror("fopen");
        return 1;
    }

    srand(time(NULL));

    for (int size_index = 0; size_index < num_sizes; size_index++)
    {
        int current_size = sizes[size_index];
        int *random_vec = malloc(current_size * sizeof(int));

        // create random vector
        for (int i = 0; i < current_size; i++)
        {
            random_vec[i] = rand();
        }

        // sort it, time
        clock_t start = clock();
        bubble_sort(random_vec, current_size);
        clock_t end = clock();

        double elapsed = (double)(end - start) / CLOCKS_PER_SEC;

        fprintf(f, "%d %lf\n", current_size, elapsed);
        printf("%d %lf\n", current_size, elapsed);
        free(random_vec);
    }

    fclose(f);

    // Launch gnuplot
    // The -persist flag keeps the window open
    system("gnuplot -persist -e \""
           "set xlabel 'N'; set ylabel 'Time (s)'; "
           "plot 'bubble_sort_time_data.txt' using 1:2 with linespoints title 'insertion Sort'\"");
    /*system("gnuplot -persist -e; "
           "set xlabel \"N\"; set ylabel \"Time (s)\"; "
           "plot \"bubble_sort_time_data.txt\" using 1:2 with linespoints title \"Bubble Sort\"'");*/
    return 0;
}