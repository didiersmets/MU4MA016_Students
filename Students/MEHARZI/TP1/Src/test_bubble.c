#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubble_sort(int *T, int n);

int main(void) {
    // tailles demandées par l’énoncé
    int Ns[] = {10, 20, 50, 100, 200, 500, 1000};
    int nbN = sizeof(Ns)/sizeof(Ns[0]);

    // fichier de sortie pour gnuplot
    FILE *f = fopen("bubble_times.dat", "w");
    if (!f) {
        printf("Erreur: impossible d'ouvrir bubble_times.dat\n");
        return 1;
    }

    srand((unsigned)time(NULL));

    for (int k = 0; k < nbN; k++) {
        int N = Ns[k];
        int *T = (int*)malloc(N * sizeof(int));
        if (!T) { printf("malloc a echoue\n"); fclose(f); return 1; }

        // génère N entiers aléatoires
        for (int i = 0; i < N; i++) T[i] = rand();

        // mesure du temps
        clock_t t0 = clock();
        bubble_sort(T, N);
        clock_t t1 = clock();

        double seconds = (double)(t1 - t0) / CLOCKS_PER_SEC;

        // enregistre et affiche
        fprintf(f, "%d %.8f\n", N, seconds);
        printf("N=%4d  time=%.6f s\n", N, seconds);

        free(T);
    }

    fclose(f);

    return 0;
}
