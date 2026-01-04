/*
 * tp1_q2_sorts.c
 *
 * TP1 - Question 2: Bubble sort, insertion sort, merge sort + benchmarking + gnuplot
 *
 * Requirements (as shown in the statement):
 * - Implement 3 sorting algorithms among the simplest:
 *     1) bubble sort
 *     2) insertion sort
 *     3) merge sort (with a MERGE subroutine)
 *
 * - For each sorting algorithm, write a function:
 *       void sort_name(int *T, int n);
 *   where:
 *     T is the address of an array of integers
 *     n is the number of elements
 *   and with no return value (in-place modification).
 *
 * - Then write a main program that:
 *   1) loops over N in {10, 20, 50, 100, 200, 500, 1000} and for each N:
 *        - generates an array of N random integers
 *        - calls the sorting algorithm
 *        - measures execution time and records it
 *   2) writes (N vs time) into a file suitable for gnuplot
 *   3) launches gnuplot through a system() call with log scale on both axes
 *
 * Notes:
 * - Bubble/insertion are O(N^2) and will be slower for larger N than merge sort (O(N log N)).
 * - Merge sort cannot fully work in-place without extra complexity; we use a temporary buffer
 *   allocated once (recommended to avoid repeated malloc/free inside recursion).
 */

#include <stdio.h>      /* printf, fprintf, fopen, fclose */
#include <stdlib.h>     /* malloc, free, rand, srand, system */
#include <string.h>     /* memcpy */
#include <time.h>       /* time (for srand), clock_gettime */
#include <errno.h>      /* errno */
#include <assert.h>     /* assert */

/* ----------------------------- Utility: timing ----------------------------- */

/*
 * Return current time in seconds using a monotonic clock (best for benchmarking).
 * - clock_gettime(CLOCK_MONOTONIC, ...) measures elapsed time unaffected by wall-clock changes.
 */
static double now_seconds(void)
{
    struct timespec ts;

    /* clock_gettime returns 0 on success; if it fails, we fail fast for a TP. */
    int rc = clock_gettime(CLOCK_MONOTONIC, &ts);
    assert(rc == 0);

    /* Convert seconds + nanoseconds to a single double-precision seconds value. */
    return (double)ts.tv_sec + (double)ts.tv_nsec / 1e9;
}

/* -------------------------- Sorting 1: Bubble sort ------------------------- */

/*
 * Bubble sort:
 * - Repeatedly sweep through the array swapping adjacent out-of-order elements.
 * - After the i-th pass, the largest element among the remaining unsorted prefix
 *   is "bubbled" to its final position at the end.
 *
 * Signature required by the statement:
 *   - input: int* (array), int (size)
 *   - no return value (in-place sort)
 */
void bubble_sort(int *T, int n)
{
    /* Defensive: if n <= 1, the array is already sorted. */
    if (n <= 1) {
        return;
    }

    /* Outer loop: number of passes. After each pass, one more element is fixed at the end. */
    for (int pass = 0; pass < n - 1; pass++) {

        /* Optimization: track whether we swapped anything this pass.
         * If no swaps happen, the array is already sorted and we can stop early.
         */
        int swapped = 0;

        /* Inner loop: compare adjacent pairs up to the last unsorted index (n-1-pass). */
        for (int i = 0; i < n - 1 - pass; i++) {
            if (T[i] > T[i + 1]) {
                /* Swap T[i] and T[i+1] */
                int tmp = T[i];
                T[i] = T[i + 1];
                T[i + 1] = tmp;

                swapped = 1;
            }
        }

        /* If no swap occurred in this pass, the array is sorted. */
        if (!swapped) {
            break;
        }
    }
}

/* ------------------------ Sorting 2: Insertion sort ------------------------ */

/*
 * Insertion sort:
 * - Maintains a sorted prefix [0..k-1].
 * - Inserts element k into the correct position within the sorted prefix by shifting.
 *
 * Often efficient for small arrays; also commonly used inside more complex sorts.
 */
void insertion_sort(int *T, int n)
{
    if (n <= 1) {
        return;
    }

    /* Start from the second element, and insert it into the sorted prefix to its left. */
    for (int k = 1; k < n; k++) {

        /* The element we want to insert into the sorted prefix. */
        int key = T[k];

        /* j scans leftwards through the sorted part to find insertion position. */
        int j = k - 1;

        /* Shift elements right while they are larger than key. */
        while (j >= 0 && T[j] > key) {
            T[j + 1] = T[j];
            j--;
        }

        /* Insert key into the "hole" created by shifting. */
        T[j + 1] = key;
    }
}

/* -------------------------- Sorting 3: Merge sort -------------------------- */

/*
 * MERGE subroutine (as described in the statement):
 * Input:
 * - T: the array
 * - p, q, r: indices with p <= q < r
 * Assumption:
 * - T[p..q] is already sorted
 * - T[q+1..r] is already sorted
 * Output:
 * - T[p..r] becomes sorted after merging
 *
 * Implementation detail:
 * - We use an auxiliary buffer tmp[] of same size as T.
 * - We merge into tmp[p..r], then copy back into T[p..r].
 */

/* Merge T[p..q] and T[q+1..r] into sorted order using tmp as auxiliary storage. */
static void merge(int *T, int *tmp, int p, int q, int r)
{
    /* i points into left sorted half, j points into right sorted half. */
    int i = p;
    int j = q + 1;

    /* k is the write index into tmp. We write from p..r. */
    int k = p;

    /* While both halves still have elements, pick the smaller front element. */
    while (i <= q && j <= r) {
        if (T[i] <= T[j]) {
            tmp[k++] = T[i++];
        } else {
            tmp[k++] = T[j++];
        }
    }

    /* If any elements remain in the left half, copy them. */
    while (i <= q) {
        tmp[k++] = T[i++];
    }

    /* If any elements remain in the right half, copy them. */
    while (j <= r) {
        tmp[k++] = T[j++];
    }

    /* Copy merged range back into the original array. */
    for (int idx = p; idx <= r; idx++) {
        T[idx] = tmp[idx];
    }
}

/* Recursive merge sort over T[p..r] (inclusive). */
static void merge_sort_rec(int *T, int *tmp, int p, int r)
{
    /* Base case: 0 or 1 element. Already sorted. */
    if (p >= r) {
        return;
    }

    /* q = floor((p+r)/2), as in the pseudo-code. */
    int q = p + (r - p) / 2;

    /* Recursively sort left half, then right half. */
    merge_sort_rec(T, tmp, p, q);
    merge_sort_rec(T, tmp, q + 1, r);

    /* Merge the two sorted halves. */
    merge(T, tmp, p, q, r);
}

/*
 * Public merge sort function with the required signature:
 * - Allocates a temporary buffer once, calls recursive sort, then frees it.
 */
void merge_sort(int *T, int n)
{
    if (n <= 1) {
        return;
    }

    /* Allocate auxiliary array for merges (same size as T). */
    int *tmp = (int *)malloc((size_t)n * sizeof(int));
    if (tmp == NULL) {
        /* If allocation fails, we cannot proceed; fail fast for TP context. */
        fprintf(stderr, "merge_sort: malloc failed\n");
        exit(EXIT_FAILURE);
    }

    /* Sort entire array: p=0, r=n-1 as stated. */
    merge_sort_rec(T, tmp, 0, n - 1);

    /* Prevent memory leak: free auxiliary buffer. */
    free(tmp);
}

/* -------------------------- Benchmarking / Main ---------------------------- */

/*
 * Benchmark settings:
 * - The statement requires measuring time for each N once; in practice,
 *   timing can be noisy, so we average across multiple runs.
 * - You can set REPEATS to 1 to match the most literal reading.
 */
#define REPEATS 5

/* Fill an array with random integers. */
static void fill_random_ints(int *T, int n)
{
    /* Use a moderate range so values vary but remain within int. */
    for (int i = 0; i < n; i++) {
        T[i] = rand(); /* rand() returns a pseudo-random int in [0, RAND_MAX]. */
    }
}

/*
 * Time a sorting function of type: void (*sort_fn)(int*, int)
 * - base[] is the original data
 * - work[] is a scratch copy we sort (so each algorithm sorts the same input)
 * Returns: average elapsed seconds over REPEATS runs.
 */
static double time_sort(void (*sort_fn)(int *, int), const int *base, int *work, int n)
{
    double total = 0.0;

    for (int rep = 0; rep < REPEATS; rep++) {

        /* Copy base data into work array so each run sorts identical input. */
        memcpy(work, base, (size_t)n * sizeof(int));

        /* Time the sort. */
        double t0 = now_seconds();
        sort_fn(work, n);
        double t1 = now_seconds();

        total += (t1 - t0);
    }

    return total / (double)REPEATS;
}

int main(void)
{
    /* N values required by the statement. */
    const int Ns[] = {10, 20, 50, 100, 200, 500, 1000};
    const int num_Ns = (int)(sizeof(Ns) / sizeof(Ns[0]));

    /* Seed PRNG so each program run gets different random arrays. */
    srand((unsigned int)time(NULL));

    /* Output data file for gnuplot: columns = N, bubble, insertion, merge */
    const char *data_filename = "sort_times.dat";
    FILE *out = fopen(data_filename, "w");
    if (out == NULL) {
        fprintf(stderr, "Failed to open %s for writing (errno=%d)\n", data_filename, errno);
        return EXIT_FAILURE;
    }

    /* gnuplot ignores lines starting with #, so we can include a helpful header. */
    fprintf(out, "# N  bubble_seconds  insertion_seconds  merge_seconds\n");

    /* For each N, generate random data, time each algorithm, and record results. */
    for (int idx = 0; idx < num_Ns; idx++) {
        int n = Ns[idx];

        /* Allocate arrays:
         * - base: original random integers
         * - work: scratch array for sorting
         */
        int *base = (int *)malloc((size_t)n * sizeof(int));
        int *work = (int *)malloc((size_t)n * sizeof(int));

        if (base == NULL || work == NULL) {
            fprintf(stderr, "malloc failed for n=%d\n", n);
            free(base);
            free(work);
            fclose(out);
            return EXIT_FAILURE;
        }

        /* Generate data once per N. */
        fill_random_ints(base, n);

        /* Time each sorting algorithm on identical input (by copying base -> work). */
        double tbubble    = time_sort(bubble_sort,    base, work, n);
        double tinsertion = time_sort(insertion_sort, base, work, n);
        double tmerge     = time_sort(merge_sort,     base, work, n);

        /* Write one line: N and times in seconds. */
        fprintf(out, "%d %.12f %.12f %.12f\n", n, tbubble, tinsertion, tmerge);

        /* Clean up. */
        free(base);
        free(work);

        /* Optional: also print to console so you see progress. */
        printf("N=%d  bubble=%.6e  insertion=%.6e  merge=%.6e\n", n, tbubble, tinsertion, tmerge);
    }

    fclose(out);

    /* Create a gnuplot script file and call gnuplot via system(), as required. */
    const char *gp_filename = "plot_sort_times.gp";
    FILE *gp = fopen(gp_filename, "w");
    if (gp == NULL) {
        fprintf(stderr, "Failed to open %s for writing (errno=%d)\n", gp_filename, errno);
        return EXIT_FAILURE;
    }

    /* gnuplot commands:
     * - logscale on both axes
     * - grid for readability
     * - plot each time series from the same file using different columns
     */
    fprintf(gp,
            "set title 'Sorting benchmark (log-log)'\n"
            "set xlabel 'N (array size)'\n"
            "set ylabel 'Execution time (seconds)'\n"
            "set logscale xy\n"
            "set grid\n"
            "set key left top\n"
            "plot \\\n"
            "  '%s' using 1:2 with linespoints title 'bubble sort', \\\n"
            "  '%s' using 1:3 with linespoints title 'insertion sort', \\\n"
            "  '%s' using 1:4 with linespoints title 'merge sort'\n",
            data_filename, data_filename, data_filename);

    fclose(gp);

    /* Launch gnuplot.
     * - -persist keeps the window open after plotting (common for interactive use).
     * - If gnuplot is not installed, this call will fail; your program still generated the data file.
     */
    {
        char cmd[256];
        snprintf(cmd, sizeof(cmd), "gnuplot -persist %s", gp_filename);
        int rc = system(cmd);

        /* If rc != 0, gnuplot failed to run; we do not treat it as fatal. */
        if (rc != 0) {
            fprintf(stderr,
                    "Warning: gnuplot did not run successfully (system rc=%d).\n"
                    "Data is available in %s and script in %s.\n",
                    rc, data_filename, gp_filename);
        }
    }

    return EXIT_SUCCESS;
}
