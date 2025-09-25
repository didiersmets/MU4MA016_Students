#include <stdio.h>
#include <stdlib.h>     // pour rand, atoi, srand
#include <time.h>       // pour time (initialisation du rand)
#include "../include/circular_buffer_queue.h"

int main(int argc, char *argv[]) {
    // Vérification de la ligne de commande
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nombre_de_tirages>\n", argv[0]);
        return 1;
    }

    // Lire le nombre de tirages à effectuer
    int n = atoi(argv[1]);
    if (n <= 0) {
        fprintf(stderr, "Le nombre de tirages doit être positif.\n");
        return 1;
    }

    // Initialiser le générateur de nombres aléatoires
    srand((unsigned int)time(NULL));

    // Créer une file d'entiers
    struct Queue *q = queue_init(sizeof(int), 4); // capacité initiale 4
    if (!q) {
        fprintf(stderr, "Erreur lors de l'initialisation de la file.\n");
        return 1;
    }

    size_t l_max = 0; // longueur maximale atteinte par la file

    // Boucle sur les tirages aléatoires
    for (int i = 0; i < n; i++) {
        int p = rand();  // tirage aléatoire

        if (p % 2 == 0) {
            // Si p est pair, on l'enfile dans la file
            queue_enqueue(q, &p);
        } else if (!is_empty(q)) {
            // Si p est impair, on défiler un élément si la file n'est pas vide
            int tmp;
            queue_dequeue(q, &tmp); // on ne fait rien avec tmp
        }

        // Mettre à jour la longueur maximale
        if (queue_length(q) > l_max) {
            l_max = queue_length(q);
        }
    }

    // Libérer la mémoire
    queue_dispose(q);

    // Afficher la longueur maximale atteinte
    printf("%zu\n", l_max);

    // Retourner l_max en tant que code de retour (attention : cast si > 255)
    return (int)l_max;
}