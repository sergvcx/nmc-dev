#include "stdlib.h"
#include "stdio.h"
#include "../../include/nmtype.h"
#include "../../include/hadamard.h"

const int size = 1024;
long long array[size];

int main() {
	srand((unsigned) 85);
	for (int i = 0; i < size; i++) {
		array[i] = ((long long)rand()<<32) | (rand());
	}

	int hash1 = 0;
	int hash2 = 0;

	for (int i = 1; i < size; i++) {
		hash1 = nmppsHash64u((long long *) array, i);
		hash2 = nmppsHash64u((long long *) array, i+1);
		if (hash1==hash2) return hash1;
	}

	for (int i = 0; i < size; i++) {
		hash1 = nmppsHash64u((long long *) array, i+1);
		array[i] -= i+1;
		hash2 = nmppsHash64u((long long *) array, i+1);
		if (hash1==hash2) return hash2;
		array[i] += i+1;
	}

	printf("return code = 0");

	return 0;
} 