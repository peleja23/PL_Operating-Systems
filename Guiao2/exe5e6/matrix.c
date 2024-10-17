#include "matrix.h"
#include <unistd.h> 
#include <sys/wait.h>


int **createMatrix() {

    // seed random numbers
    srand(time(NULL));

    // Allocate and populate matrix with random numbers.
    printf("Generating numbers from 0 to %d...", MAX_RAND);
    int **matrix = (int **) malloc(sizeof(int*) * ROWS);
    for (int i = 0; i < ROWS; i++) {
        matrix[i] = (int*) malloc(sizeof(int) * COLUMNS);
        for (int j = 0; j < COLUMNS; j++) {
            matrix[i][j] = rand() % MAX_RAND;
        }
    }
    printf("Done.\n");

    return matrix;
}

void printMatrix(int **matrix) {

    for (int i = 0; i < ROWS; i++) {
        printf("%2d | ", i);
        for (int j = 0; j < COLUMNS; j++) {
            printf("%7d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// ex.5
int valueExists(int **matrix, int value) {
	
	int status;
    for(int i=0; i < ROWS; i++){
    	if(fork() == 0){
    		for(int j = 0; j < COLUMNS; j++){
    			if(matrix[i][j] == value){
    				_exit(0);
    			}
    		}
    		_exit(1);
    	}
    }
	for(int i = 0; i < ROWS; i++){
		wait(&status);
		if(WEXITSTATUS(status)){
			return 0;
		}
	}
	return 1;
}


// ex.6
void linesWithValue(int **matrix, int value) {
	int foundLines[ROWS];
	int foundCount = 0;
	int status;
	int a;
    for(int i=0; i < ROWS; i++){
    	if(fork() == 0){
    		for(int j = 0; j < COLUMNS; j++){
    			if(matrix[i][j] == value){
    				_exit(i+1);
    			}
    		}
    		_exit(0);
    	}
    }
	for(int i = 0; i < ROWS; i++){
		wait(&status);
		int exit_code = WEXITSTATUS(status);
		if(WEXITSTATUS(status)!=0){
			foundLines[foundCount++] = exit_code - 1;
		}
	}
	for (int i = 0; i < foundCount; i++){
		for (int j = i+1; j<foundCount; ++j){
			if (foundLines[i] > foundLines[j]){
				a = foundLines[i];
				foundLines[i] = foundLines[j];
				foundLines[j] = a;
			}
		}
	}
	for (int i = 0; i < foundCount; i++) {
		printf("o numero foi encontrado na linha %d\n", foundLines[i]);
	}
}



