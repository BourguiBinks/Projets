#include <stdlib.h>
#include <assert.h>
#include "somme.h"
 
int somme(int *T, int N, int *min_pos, int *max_pos){
	assert(N > 0 && T != NULL && min_pos != NULL && max_pos != NULL);
	int min = T[0];
	int max = T[0];
	int sum = T[0];
	int new_sum = 0;
	*min_pos = 0;
    *max_pos = 0;

	int i = 0;
	while(i < N){

		//printf("i: %d, min: %d, max: %d, sum: %d, new sum: %d\n", i, min, max, sum, new_sum);

		new_sum += T[i];

		// new minimum
		if(T[i] < min){
			// if the old min is after the max we need to extend the sum
			if(*max_pos <= *min_pos)
				sum += new_sum - T[*min_pos];  // we should not count T[min_pos] 2 times

			//if the old min is before the max we need to replace the sum
			else
				sum = new_sum;

			// we reset new_sum and change min and min_pos
			new_sum = T[i];
			min = T[i];
			*min_pos = i;
		}

		// new maximum
		if(T[i] > max){
			// if the old max is after the min we need to extend the sum
			if(*min_pos <= *max_pos)
				sum += new_sum - T[*max_pos]; // we should not count T[max_pos] 2 times

			//if the old max is before the min we need to replace the sum
			else
				sum = new_sum;

			// we reset new_sum and change max and max_pos
			new_sum = T[i];
			max = T[i];
			*max_pos = i;
		}

		// next value
		i++;
	}
	return sum;
}

