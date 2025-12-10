#include "sorting.h"
#include <stdlib.h>

static void merge_sort_rec(int *a, int left, int right);
static void merge(int *a, int left, int mid, int right);

void bubble_sort(int *a, int n)
{
    int i;
    int j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - 1 - i; j++)
        {

            if (a[j] > a[j + 1])
            {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

void insertion_sort(int *a, int n)
{
    int i;
    for (i = 1; i < n; i++)
    {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key)
        {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

void merge_sort(int *a, int n)
{
    if (n <= 1)
        return;
    merge_sort_rec(a, 0, n - 1);
}

static void merge_sort_rec(int *a, int left, int right)
{
    if (left == right)
    {
        return;
    }

    int mid = (left + right) / 2;
    merge_sort_rec(a, left, mid);
    merge_sort_rec(a, mid + 1, right);

    merge(a, left, mid, right);
}

static void merge(int *a, int left, int mid, int right)
{
    int length = right - left + 1;
    int i = left;
    int j = mid + 1;
    int k = 0;

    int *temp = malloc(length * sizeof(int));

    while (i <= mid && j <= right)
    {
        if (a[i] <= a[j])
        {
            temp[k] = a[i];
            i++;
            k++;
        }
        else
        {
            temp[k] = a[j];
            j++;
            k++;
        }
    }

    while (i <= mid)
    {
        temp[k] = a[i];
        i++;
        k++;
    }

    while (j <= right)
    {
        temp[k] = a[j];
        j++;
        k++;
    }

    for (int t = 0; t < length; t++)
    {
        a[left + t] = temp[t];
    }

    free(temp);
}