#include "matrix.h"


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
	char buf[50];
	int status;
    for(int i = 0; i < ROWS; i++){
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
		if(WIFEXITED(status) && WEXITSTATUS(status) != 1){
			int len = snprintf(buf, 50, "o valor existe\n");
			write(1, buf, len);
		}
	}
    return 0;
}


// ex.6
void linesWithValue(int **matrix, int value) {
    char buf[50];
    int status;
    int pid[ROWS];
    
    for(int i = 0; i < ROWS; i++){
    	if((pid[i] = fork()) == 0){
    		for(int j = 0; j < COLUMNS; j++){
    			if(matrix[i][j] == value){
    				_exit(i);
    			}
    		}
    		_exit(0);
    	} 
    }
    
	for(int i = 0; i < ROWS; i++){
    	waitpid(pid[i], &status, 0);
    	if(WIFEXITED(status) && WEXITSTATUS(status) != 0){
    		int len = snprintf(buf, 50, "o valor existe na linha: %d\n", WEXITSTATUS(status));
    		write(1, buf, len);
    	}
    }
}






