
#include "Sort.h"
#include "Stable.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

// For all your tests, replace the code below by the sum of the IDs of the students in 
// your grou (in the format 20221234). If you don't use the correct code, the correction
// of your project will be impossible.

const int studentcode = 20211885 + 20211381;
// const int studentcode = 211885 + 211381;

//déclaration d'une variable globale.
long unsigned int globalCount = 0;

static void swap_int(void *array, size_t i, size_t j);
static int compare_int(const void *array, size_t i, size_t j);

static void swap_int(void *array, size_t i, size_t j)
{
	int temp = ((int *)array)[i];
	((int *)array)[i] = ((int *)array)[j];
	((int *)array)[j] = temp;
}

static int compare_int(const void *array, size_t i, size_t j)
{
	globalCount++;
	return (((int *)array)[i] - ((int *)array)[j]);
}

int main(int argc, char *argv[])
{

	if (argc < 3 || argc > 4)
	{
		fprintf(stderr, "Usage: %s n algo [stable]\n   - n: the size of the random array\n "
						"  - algo: the algorithm (0,1,..., or 6})\n   - stable: (optional)"
						" run the stabilized version of the algorithm\n",
				argv[0]);
		exit(0);
	}

	// srand(42);
	srand(time(NULL));

	size_t n = atoi(argv[1]);
	size_t algo = atoi(argv[2]);
	bool stable = false;
	if (argc > 3 && strcmp(argv[3], "stable") == 0)
		stable = true;

	int *array = malloc(n * sizeof(int));
	float temps;
	float total;


	//Lance le programme 5 fois
	for(int i = 0; i < 5; ++i){

	// random array
	for (size_t i = 0; i < n; i++)
		array[i] = rand() % (n * 10) - (n * 10) / 2;


	//increasing array
	// for(size_t i = 0; i < n; i++)
	// 	array[i] = i;


	//decreasing array
	// for(size_t i = 0; i < n; i++)
	// 	array[i] = n-i;
		
	isSortStable(algo, array, n);

	printf("Sorting a random array of size %zu with algorithm %zu", n, algo);
	if (stable)
		printf(" (stabilized)\n");
	else
		printf("\n");

	if (n <= 20)
	{
		printf("Original array:\n");
		for (size_t i = 0; i < n; i++)
			printf(" %d", array[i]);

		printf("\n\n");
	}

	clock_t start = clock();

	if (stable)
		stableSort(algo, array, n, compare_int, swap_int);
	else
		sort(algo, array, n, compare_int, swap_int);

	printf("globalCount = %ld\n", globalCount);
	
	clock_t end = clock();
	temps = (double)(end - start) / (double)CLOCKS_PER_SEC;
	if (n <= 20)
	{
		printf("Ordered array:\n");
		for (size_t i = 0; i < n; i++)
		{
			printf(" %d", array[i]);
		}
		printf("\n");
	}
	printf("CPU time: %f\n", temps);
	total += temps;

}
	double moyenneTemps = (double)total / (double)5;
	printf("Moyenne des temps sur 5 exécutions: %f\n", moyenneTemps);
	free(array);
}
