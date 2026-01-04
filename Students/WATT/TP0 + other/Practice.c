#include <stdio.h>

void counter_example() {
    static int count = 0;  // keeps its value between calls
    count++;               // 1, then 2, then 3, ...
    printf("%d\n", count);
}

int main() {
    counter_example(); // prints 1
    counter_example(); // prints 2
    counter_example(); // prints 3
    counter_example(); // prints 4
    return 0;
}