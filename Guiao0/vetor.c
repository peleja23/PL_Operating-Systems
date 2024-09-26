#include <stdio.h>
#include "vetor.h"

void fill(int* vector, int size, int value){
	for(int i = 0; i < size; i++){
		vector[i] = i;
	}
}

int find(int* vector, int size, int value){
	for(int i = 0; i<=size; i++){
		if(vector[i] == value){
			return value;
		}
	}
	return -1;
}
