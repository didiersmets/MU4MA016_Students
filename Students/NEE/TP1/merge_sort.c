#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>

void merge(int *array, int start, int middle, int end);
void merge_sort(int *array, int start, int end);
void merge_sort_main(int *array, int size)
{
    // just to call with indices
    if (array == NULL || size == 0)
    {
        return;
    }
    merge_sort(array, 0, size - 1);
}

void merge_sort(int *array, int start, int end)
{
    if (start < end)
    {
        int middle = start + (end - start) / 2;
        merge_sort(array, start, middle);
        merge_sort(array, middle + 1, end);
        merge(array, start, middle, end);
    }
}

void merge(int *array, int start, int middle, int end)
{
    // first we need to allocate some memory
    int *temp_arr = malloc((end - start + 1) * sizeof(int));
    if (temp_arr == NULL){
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    // now we need three indexs
    int temp_arr_index = 0;
    int first_half_index = start;
    int second_half_index = middle + 1;

    while (first_half_index <= middle && second_half_index <= end)
    {
        if (array[first_half_index] <= array[second_half_index])
        {
            temp_arr[temp_arr_index] = array[first_half_index];
            temp_arr_index++;
            first_half_index++;
        }
        else
        {
            temp_arr[temp_arr_index] = array[second_half_index];
            temp_arr_index++;
            second_half_index++;
        }
    }
    // now were at the end. if the first one ran out of elemnts, the the biggest are already in the second half of the vector. , so we just copy the front in. otherwise its more complicates
    if (first_half_index == middle + 1)
    {
        // first half ran out of elements: we can memcopy the rest of the second vector in to the end of the temp vector
        memcpy(temp_arr + temp_arr_index, array + second_half_index, (end - second_half_index + 1) * sizeof(int));
    }
    else
    {
        // if the second half ran out of elemnts, we copy the rest of trhe first half to the end o the temp
        memcpy(temp_arr + temp_arr_index, array + first_half_index, (middle - first_half_index + 1) * sizeof(int));
    }
    // copy temp from start to end
    memcpy(array + start, temp_arr, (end - start + 1) * sizeof(int));
    free(temp_arr);
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

    merge_sort_main(test_array, test_size);

    printf("Sorted array:   ");
    for (int i = 0; i < test_size; i++)
    {
        printf("%d ", test_array[i]);
    }
    printf("\n\n");

    int start_size = 0;
    int end_size = 10000;
    int step_size = 100;
    int max_sizes = 1000;

    int *sizes = malloc(max_sizes * sizeof(int));
    if (sizes == NULL){
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    int num_sizes = 0;

    for (int size = start_size; size <= end_size; size += step_size)
    {
        sizes[num_sizes++] = size;
    }

    FILE *f = fopen("merge_sort_time_data.txt", "w");
    if (!f)
    {
        perror("fopen");
        return 1;
    }

    srand(time(NULL));

    for (int size_index = 0; size_index < num_sizes; size_index++)
    {
        int current_size = sizes[size_index];
        if (current_size == 0){
            continue;
        }
        int *random_vec = malloc(current_size * sizeof(int));
        if (random_vec == NULL){
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

        // create random vector
        for (int i = 0; i < current_size; i++)
        {
            random_vec[i] = rand() % 10000;
        }

        // sort it, time
        clock_t start = clock();
        merge_sort_main(random_vec, current_size);
        clock_t end = clock();

        double elapsed = (double)(end - start) / CLOCKS_PER_SEC;

        fprintf(f, "%d %lf\n", current_size, elapsed);
        printf("%d %lf\n", current_size, elapsed);
        free(random_vec);
    }

    fclose(f);

    // Linear scale
    system("gnuplot -persist -e \""
           "set xlabel 'N'; set ylabel 'Time (s)'; "
           "plot 'merge_sort_time_data.txt' using 1:2 with linespoints title 'merge Sort'\"");

    // Log scale
    // system("gnuplot -persist -e \"set logscale xy; "
    //        "set xlabel 'N'; set ylabel 'Time (s)'; "
    //        "plot 'merge_sort_time_data.txt' using 1:2 with linespoints title 'merge Sort'\"");
    free(sizes);
    return 0;
}