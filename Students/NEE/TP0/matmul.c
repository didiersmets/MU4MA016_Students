#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

// Function declarations
void fill_random_matrix(int *matrix, int size, int max_val);
void run_performance_tests();
void matmul_no_print(int *A, int *B, int *C, int num_rows_A, int num_cols_A, int num_rows_B, int num_cols_B);
void matmul_optimized_no_print(int *A, int *B, int *C, int num_rows_A, int num_cols_A, int num_rows_B, int num_cols_B);
void matmul(int *A, int *B, int *C, int num_rows_A, int num_cols_A, int num_rows_B, int num_cols_B);
void matmul_optimized_memory_access(int *A, int *B, int *C, int num_rows_A, int num_cols_A, int num_rows_B, int num_cols_B);

// Original functions with printing
void matmul(int *A, int *B, int *C, int num_rows_A, int num_cols_A, int num_rows_B, int num_cols_B)
{
    printf("Matrix A:\n");
    for (int i = 0; i < num_rows_A; i++)
    {
        for (int j = 0; j < num_cols_A; j++)
        {
            printf("%d ", A[i * num_cols_A + j]);
        }
        printf("\n");
    }

    // Optional: print B
    printf("Matrix B:\n");
    for (int i = 0; i < num_rows_B; i++)
    {
        for (int j = 0; j < num_cols_B; j++)
        {
            printf("%d ", B[i * num_cols_B + j]);
        }
        printf("\n");
    }

    // Compute C
    for (int i = 0; i < num_rows_A; i++)
    {
        for (int j = 0; j < num_cols_B; j++)
        {
            for (int k = 0; k < num_cols_A; k++)
            {
                C[i * num_cols_B + j] += A[i * num_cols_A + k] * B[k * num_cols_B + j];
            }
        }
    }
}

void matmul_optimized_memory_access(int *A, int *B, int *C, int num_rows_A, int num_cols_A, int num_rows_B, int num_cols_B)
{
    printf("Matrix A:\n");
    for (int i = 0; i < num_rows_A; i++)
    {
        for (int j = 0; j < num_cols_A; j++)
        {
            printf("%d ", A[i * num_cols_A + j]);
        }
        printf("\n");
    }
    printf("\n");

    // Optional: print B
    printf("Matrix B:\n");
    for (int i = 0; i < num_rows_B; i++)
    {
        for (int j = 0; j < num_cols_B; j++)
        {
            printf("%d ", B[i * num_cols_B + j]);
        }
        printf("\n");
    }
    printf("\n");

    // Compute C - optimized loop order (i-k-j)
    for (int i = 0; i < num_rows_A; i++)
    {
        for (int j = 0; j < num_cols_A; j++) // This is actually k in standard notation
        {
            for (int k = 0; k < num_cols_B; k++) // This is actually j in standard notation
            {
                C[i * num_cols_B + k] += A[i * num_cols_A + j] * B[j * num_cols_B + k];
            }
        }
    }
}

// Silent versions for performance testing (no printing)
void matmul_no_print(int *A, int *B, int *C, int num_rows_A, int num_cols_A, int num_rows_B, int num_cols_B)
{
    for (int i = 0; i < num_rows_A; i++)
    {
        for (int j = 0; j < num_cols_B; j++)
        {
            for (int k = 0; k < num_cols_A; k++)
            {
                C[i * num_cols_B + j] += A[i * num_cols_A + k] * B[k * num_cols_B + j];
            }
        }
    }
}

void matmul_optimized_no_print(int *A, int *B, int *C, int num_rows_A, int num_cols_A, int num_rows_B, int num_cols_B)
{
    for (int i = 0; i < num_rows_A; i++)
    {
        for (int j = 0; j < num_cols_A; j++)
        { // This is actually k
            for (int k = 0; k < num_cols_B; k++)
            { // This is actually j
                C[i * num_cols_B + k] += A[i * num_cols_A + j] * B[j * num_cols_B + k];
            }
        }
    }
}

void run_test(const char *test_name, int *A, int *B, int *C,
              int num_rows_A, int num_cols_A, int num_rows_B, int num_cols_B)
{
    printf("\n=== %s ===\n", test_name);

    // Clear C for this test
    for (int i = 0; i < num_rows_A * num_cols_B; i++)
    {
        C[i] = 0;
    }

    matmul_optimized_memory_access(A, B, C, num_rows_A, num_cols_A, num_rows_B, num_cols_B);

    printf("Result C:\n");
    for (int i = 0; i < num_rows_A; i++)
    {
        for (int j = 0; j < num_cols_B; j++)
        {
            printf("%d ", C[i * num_cols_B + j]);
        }
        printf("\n");
    }
}

int main()
{
    printf("Matrix Multiplication Test Suite\n");
    printf("================================\n");

    // Test 1: Identity Matrix (2x2)
    {
        int num_rows_A = 2, num_cols_A = 2, num_rows_B = 2, num_cols_B = 2;
        int *A = malloc(4 * sizeof(int));
        int *B = malloc(4 * sizeof(int));
        int *C = calloc(4, sizeof(int));

        // A = [2 3]
        //     [1 4]
        A[0] = 2;
        A[1] = 3;
        A[2] = 1;
        A[3] = 4;

        // B = Identity matrix [1 0]
        //                     [0 1]
        B[0] = 1;
        B[1] = 0;
        B[2] = 0;
        B[3] = 1;

        run_test("Test 1: A * Identity = A", A, B, C, num_rows_A, num_cols_A, num_rows_B, num_cols_B);
        printf("Expected: [2 3] [1 4]\n");

        free(A);
        free(B);
        free(C);
    }

    // Test 2: Simple 2x2 multiplication
    {
        int num_rows_A = 2, num_cols_A = 2, num_rows_B = 2, num_cols_B = 2;
        int *A = malloc(4 * sizeof(int));
        int *B = malloc(4 * sizeof(int));
        int *C = calloc(4, sizeof(int));

        // A = [1 2]    B = [5 6]
        //     [3 4]        [7 8]
        A[0] = 1;
        A[1] = 2;
        B[0] = 5;
        B[1] = 6;
        A[2] = 3;
        A[3] = 4;
        B[2] = 7;
        B[3] = 8;

        run_test("Test 2: Simple 2x2", A, B, C, num_rows_A, num_cols_A, num_rows_B, num_cols_B);
        printf("Expected: [19 22] [43 50]\n");

        free(A);
        free(B);
        free(C);
    }

    // Test 3: Rectangle matrices
    {
        int num_rows_A = 3, num_cols_A = 2, num_rows_B = 2, num_cols_B = 4;
        int *A = malloc(6 * sizeof(int));
        int *B = malloc(8 * sizeof(int));
        int *C = calloc(12, sizeof(int));

        // A = [1 0]
        //     [0 1]
        //     [1 1]
        A[0] = 1;
        A[1] = 0;
        A[2] = 0;
        A[3] = 1;
        A[4] = 1;
        A[5] = 1;

        // B = [2 1 0 3]
        //     [1 2 1 0]
        B[0] = 2;
        B[1] = 1;
        B[2] = 0;
        B[3] = 3;
        B[4] = 1;
        B[5] = 2;
        B[6] = 1;
        B[7] = 0;

        run_test("Test 3: 3x2 * 2x4", A, B, C, num_rows_A, num_cols_A, num_rows_B, num_cols_B);
        printf("Expected: [2 1 0 3] [1 2 1 0] [3 3 1 3]\n");

        free(A);
        free(B);
        free(C);
    }

    // Test 4: All ones
    {
        int num_rows_A = 2, num_cols_A = 3, num_rows_B = 3, num_cols_B = 2;
        int *A = malloc(6 * sizeof(int));
        int *B = malloc(6 * sizeof(int));
        int *C = calloc(4, sizeof(int));

        // Fill with all 1s
        for (int i = 0; i < 6; i++)
        {
            A[i] = 1;
            B[i] = 1;
        }

        run_test("Test 4: All ones", A, B, C, num_rows_A, num_cols_A, num_rows_B, num_cols_B);
        printf("Expected: [3 3] [3 3]\n");

        free(A);
        free(B);
        free(C);
    }

    // Test 5: Your original test
    {
        int num_rows_A = 4, num_cols_A = 2, num_rows_B = 2, num_cols_B = 6;
        int *A = malloc(8 * sizeof(int));
        int *B = malloc(12 * sizeof(int));
        int *C = calloc(24, sizeof(int));

        // A = [1 2]
        //     [3 4]
        //     [5 6]
        //     [7 8]
        A[0] = 1;
        A[1] = 2;
        A[2] = 3;
        A[3] = 4;
        A[4] = 5;
        A[5] = 6;
        A[6] = 7;
        A[7] = 8;

        // B = [1 0 1 0 1 0]
        //     [0 1 0 1 0 1]
        B[0] = 1;
        B[1] = 0;
        B[2] = 1;
        B[3] = 0;
        B[4] = 1;
        B[5] = 0;
        B[6] = 0;
        B[7] = 1;
        B[8] = 0;
        B[9] = 1;
        B[10] = 0;
        B[11] = 1;

        run_test("Test 5: Original test", A, B, C, num_rows_A, num_cols_A, num_rows_B, num_cols_B);
        printf("Expected: [1 2 1 2 1 2] [3 4 3 4 3 4] [5 6 5 6 5 6] [7 8 7 8 7 8]\n");

        free(A);
        free(B);
        free(C);
    }

    // Test 6: Edge case - single elements
    {
        int num_rows_A = 1, num_cols_A = 1, num_rows_B = 1, num_cols_B = 1;
        int *A = malloc(1 * sizeof(int));
        int *B = malloc(1 * sizeof(int));
        int *C = calloc(1, sizeof(int));

        A[0] = 5;
        B[0] = 7;

        run_test("Test 6: 1x1 matrices", A, B, C, num_rows_A, num_cols_A, num_rows_B, num_cols_B);
        printf("Expected: [35]\n");

        free(A);
        free(B);
        free(C);
    }

    printf("\n=== All tests completed ===\n");

    // Performance benchmarks
    printf("\n");
    run_performance_tests();

    return 0;
}

void fill_random_matrix(int *matrix, int size, int max_val)
{
    for (int i = 0; i < size; i++)
    {
        matrix[i] = rand() % max_val + 1;
    }
}

void run_performance_tests()
{
    printf("=== Performance Benchmarks ===\n");
    printf("Matrix Size    | Standard (ms) | Optimized (ms) | Speedup\n");
    printf("--------------------------------------------------------\n");

    srand(time(NULL));

    // Test different matrix sizes
    int sizes[] = {50, 100, 200, 400}; // Reduced max size for faster compilation
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int s = 0; s < num_sizes; s++)
    {
        int n = sizes[s];

        // Create square matrices n x n
        int *A = malloc(n * n * sizeof(int));
        int *B = malloc(n * n * sizeof(int));
        int *C1 = calloc(n * n, sizeof(int)); // For standard
        int *C2 = calloc(n * n, sizeof(int)); // For optimized

        // Fill with random values
        fill_random_matrix(A, n * n, 10);
        fill_random_matrix(B, n * n, 10);

        // Test standard implementation
        clock_t start = clock();
        matmul_no_print(A, B, C1, n, n, n, n);
        clock_t end = clock();
        double time_standard = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;

        // Clear C2 and test optimized implementation
        memset(C2, 0, n * n * sizeof(int));
        start = clock();
        matmul_optimized_no_print(A, B, C2, n, n, n, n);
        end = clock();
        double time_optimized = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;

        // Verify results are identical
        bool results_match = true;
        for (int i = 0; i < n * n; i++)
        {
            if (C1[i] != C2[i])
            {
                results_match = false;
                break;
            }
        }

        double speedup = time_standard / time_optimized;

        printf("%3dx%-3d       | %10.2f    | %11.2f    | %.2fx %s\n",
               n, n, time_standard, time_optimized, speedup,
               results_match ? "✓" : "✗");

        free(A);
        free(B);
        free(C1);
        free(C2);
    }

    printf("\n");

    // Test rectangular matrices
    printf("=== Rectangular Matrix Tests ===\n");
    printf("Dimensions     | Standard (ms) | Optimized (ms) | Speedup\n");
    printf("--------------------------------------------------------\n");

    // Different shapes to test
    struct
    {
        int rows_A, cols_A, rows_B, cols_B;
    } shapes[] = {
        {100, 50, 50, 200}, // Tall x Wide
        {200, 25, 25, 400}, // Very tall x Very wide
        {500, 10, 10, 500}, // Very tall x Very wide (thin middle)
        {50, 200, 200, 50}, // Wide x Tall
        {25, 400, 400, 25}, // Very wide x Very tall
        {1000, 1000, 1000, 1000},
        {2000, 2000, 2000, 2000},
        {3000, 3000, 3000, 3000},
        //{4000, 4000, 4000, 4000},
        //{5000, 5000, 5000, 5000},
        

    };

    int num_shapes = sizeof(shapes) / sizeof(shapes[0]);

    for (int s = 0; s < num_shapes; s++)
    {
        int rA = shapes[s].rows_A, cA = shapes[s].cols_A;
        int rB = shapes[s].rows_B, cB = shapes[s].cols_B;

        int *A = malloc(rA * cA * sizeof(int));
        int *B = malloc(rB * cB * sizeof(int));
        int *C1 = calloc(rA * cB, sizeof(int));
        int *C2 = calloc(rA * cB, sizeof(int));

        fill_random_matrix(A, rA * cA, 10);
        fill_random_matrix(B, rB * cB, 10);

        // Standard
        clock_t start = clock();
        matmul_no_print(A, B, C1, rA, cA, rB, cB);
        clock_t end = clock();
        double time_standard = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;

        // Optimized
        memset(C2, 0, rA * cB * sizeof(int));
        start = clock();
        matmul_optimized_no_print(A, B, C2, rA, cA, rB, cB);
        end = clock();
        double time_optimized = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;

        // Verify
        bool results_match = true;
        for (int i = 0; i < rA * cB; i++)
        {
            if (C1[i] != C2[i])
            {
                results_match = false;
                break;
            }
        }

        double speedup = time_standard / time_optimized;

        printf("%3dx%-3d x %3dx%-3d | %10.2f    | %11.2f    | %.2fx %s\n",
               rA, cA, rB, cB, time_standard, time_optimized, speedup,
               results_match ? "✓" : "✗");

        free(A);
        free(B);
        free(C1);
        free(C2);
    }

    printf("\n✓ = Results match, ✗ = Results differ\n");
}