#include <stdio.h>
int main(void)
{
    int n = 5;
    for (int i = 0; i < n; i++)
    {
        int val = 1;
        for (int k = 0; k <= i; k++)
        {
            printf("%d ", val);
            val = val * (i - k) / (k + 1);
        }
        printf("\n");
    }

    return 0;
}