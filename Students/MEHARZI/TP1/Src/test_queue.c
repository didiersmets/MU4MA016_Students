#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "circular_buffer_queue.h"

// Test simple avec une queue d'entiers
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        return 1;
    }
    long n = strtol(argv[1], NULL, 10);
    if (n <= 0) {
        fprintf(stderr, "n must be > 0\n");
        return 1;
    }

    struct Queue *q = queue_init(sizeof(int), 8); // petite capacité initiale pour tester l'agrandissement
    if (!q) {
        fprintf(stderr, "queue_init failed\n");
        return 1;
    }

    srand((unsigned)time(NULL));
    size_t l_max = 0;

    for (long k = 0; k < n; ++k) {
        int p = rand(); // grand entier >=0
        if ((p % 2) == 0) {
            // pair -> enqueue
            queue_enqueue(q, &p);
            if (queue_length(q) > l_max) l_max = queue_length(q);
        } else {
            // impair -> dequeue si non vide
            if (!is_empty(q)) {
                int sink = 0;
                queue_dequeue(q, &sink); // on jette la valeur
            }
        }
    }

    printf("l_max = %zu\n", l_max);
    queue_dispose(q);

    // Le sujet dit "le main doit retourner l_max" → si l_max dépasse 255, ça sera tronqué en code de retour.
    // On l'affiche déjà ci-dessus On renvoie au moins l_max % 256 pour respecter l’énoncé.
    return (int)(l_max % 256);
}
