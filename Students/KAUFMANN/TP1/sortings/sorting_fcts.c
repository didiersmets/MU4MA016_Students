#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

void bubble_sort(int *list, int N) {
    for (int n=N; n>1; n--) {
        for (int i=0; i<n-1; i++) {
            
            int key = list[i];
            if (key > list[i+1]) {
                list[i] = list[i+1];
                list[i+1] = key;
            }
        }
    }
}

void insertion_sort(int *list, int N) {
    for (int i = 1; i < N; i++) {
        int key = list[i];
        int j = i - 1;

        while (j >= 0 && list[j] > key) {
            list[j+1] = list[j];
            j--;
        }
        list[j+1] = key;
    }
}

static void merge(int *A, int nbA, int *B, int nbB, int *C) {
    int idxA = 0, idxB = 0;
    int idxC = 0;

    while (idxA < nbA && idxB < nbB) {
        if (A[idxA] < B[idxB]) {
            C[idxC++] = A[idxA++];
        } else {
            C[idxC++] = B[idxB++];
        }
    }
    while (idxA < nbA) {
        C[idxC++] = A[idxA++];
    }
    while (idxB < nbB) {
        C[idxC++] = B[idxB++];
    }
}


void merge_sort(int *list, int p, int r, int *mem) {
    if (p<r) {
        int q = floor((p+r)/2);
        merge_sort(list,p,q,mem);
        merge_sort(list,q+1,r,mem);
        merge(list+p, q-p+1, list+q+1, r-q, mem+p);

        for (int i=p; i<=r; i++) {
        list[i] = mem[i];
    }
    }
}

int main() {
    int sizes[] = {10, 20, 50, 100, 200, 500, 1000};
    int nb_sizes = sizeof(sizes) / sizeof(sizes[0]);
    char algo;

    printf("Algo used (b = bubble, i = insertion, m = merge): ");
    scanf(" %c", &algo);

    FILE *fp = fopen("resultats.dat", "w");
    if (!fp) {
        perror("Erreur ouverture fichier");
        return 1;
    }

    fprintf(fp, "# Taille Temps(sec)\n");

    for (int i = 0; i < nb_sizes; i++) {
        int n = sizes[i];

        int *list = malloc(sizeof(int) * n);
        int *mem  = malloc(sizeof(int) * n);
        if (!list || !mem) {
            perror("malloc");
            return 1;
        }

        for (int j = 0; j < n; j++) {
            list[j] = rand();
        }

        clock_t start = clock();

        if (algo == 'b') {
            bubble_sort(list, n);
        } else if (algo == 'i') {
            insertion_sort(list, n);
        } else if (algo == 'm') {
            merge_sort(list, 0, n - 1, mem);
        } else {
            printf("Algorithme inconnu\n");
            return 1;
        }

        clock_t end = clock();
        double elapsed = (double)(end - start) / CLOCKS_PER_SEC;

        fprintf(fp, "%d %f\n", n, elapsed);
        printf("Taille %d : %f sec\n", n, elapsed);

        free(list);
        free(mem);
    }

    fclose(fp);

    return 0;
}