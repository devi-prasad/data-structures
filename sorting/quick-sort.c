#include <stdint.h>
#include <stdio.h>

#define SWAP(a, i, j) { \
    int32_t t = arr[i]; \
    arr[i] = arr[j];    \
    arr[j] = t;         \
}

int32_t partition(int32_t arr[], int32_t p, int32_t r)
{
    int32_t x = arr[r];
    int32_t i = p-1;
    int32_t j, k;

    printf("  partition: p = %d, r = %d, x = %d\n", p, r, arr[r]);
    printf("    "); for (k = 0; k < 10; k++) printf(" %d ", arr[k]);
    printf("\n");
    for (j = p; j < r; j++) {
    	if (arr[j] <= x) {
    		i = i + 1;
    		SWAP(arr, i, j);
    		printf("     swap: i = %d, j = %d", i, j);
    		printf("     swap: arr[%d]-arr[%d] - %d and %d\n", i, j, arr[i], arr[j]);
    	}
    }
    SWAP(arr, (i+1), r)
    printf("    "); for (k = 0; k < 10; k++) printf(" %d ", arr[k]);
    return i+1;
}

void quicksort(int32_t arr[], int32_t p, int32_t r)
{
	static int call = 0;

    if (p < r) {
    	++call;
    	int32_t q = partition(arr, p, r);
    	printf("    q = %d\n", q);
    	printf("  call %d: quicksort %d %d  ", call, p, q-1);
    	printf("  call %d: quicksort %d %d\n", call, q+1, r);
    	quicksort(arr, p, q-1);
    	quicksort(arr, q+1, r);
    }
}


int main()
{
	//int32_t a[] = {70, 33, 40, 25, 20, 40, 75, 22, 63, 18};
    int32_t a[] = {74, 17, 33, 18, 63, 8, 23, 5, 43, 3};
    int32_t i;

	quicksort(a, 0, 9);

	for (i = 0; i < 10; i++) {
		printf(" %d ", a[i]);
	}
	printf("\n\n");
}
