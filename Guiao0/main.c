#include <stdio.h>
#include <stdlib.h>
#include "vetor.h"

int main(int argc, char *argv[]){

	int size = atoi(argv[1]);
	int vector[size];
	int value = atoi(argv[2]);
	fill(vector, size, value);
	int result = find(vector, size, value);
	printf("valor encontrado na posicao %d\n", result);
	
	return 0;
}
