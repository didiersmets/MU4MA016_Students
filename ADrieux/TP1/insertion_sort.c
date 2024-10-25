#include <stdlib.h>
#include <stdio.h>

void insertion_sort(int *A, int size)
{ 
	for (int i = 1; i < size; i++)
	{
		int j = i;
		while (j>0 && A[j-1] > A[j])
		{
			int tmp = A[j];
			A[j] = A[j-1];
			A[j-1] = tmp;
			j = j-1;
		}
	}
}

int main(int argc, char** argv)
{

}

