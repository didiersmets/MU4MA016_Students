#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../include/circular_buffer_queuecpp.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <nombre_de_tirages>\n";
        return 1;
    }

    int n = std::atoi(argv[1]);
    if (n <= 0) {
        std::cerr << "Le nombre de tirages doit être positif.\n";
        return 1;
    }

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    Queue<int> q(4);
    size_t l_max = 0;

    for (int i = 0; i < n; i++) {
        int p = std::rand();
        if (p % 2 == 0) {
            q.enqueue(p);
        } else if (!q.is_empty()) {
            q.dequeue();
        }
        if (q.size() > l_max) l_max = q.size();
    }

    std::cout << l_max << std::endl;
    return static_cast<int>(l_max);
}

template class Queue<int>; // instanciation explicite
