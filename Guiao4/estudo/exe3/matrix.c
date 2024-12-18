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
	int found = 0;
	int pid[ROWS];
	int found_V[ROWS];
	int pd[2];
	pipe(pd);
	
	for(int i = 0; i < ROWS; i++){
    	if((pid[i] = fork()) == 0){
    		close(pd[0]);
    		for(int j = 0; j< COLUMNS; j++){
    			if(value == matrix[i][j]){
    				found++;
    			}
    		}
    		write(pd[1], &found, sizeof(int));
    		close(pd[1]);
    		_exit(i+1);
    	}
	}
	
	close(pd[1]);
	for(int i = 0; i < ROWS; i++){
    	waitpid(pid[i], &status, 0);
    	read(pd[0], &found_V[i], sizeof(int));
    	if(WIFEXITED(status)){
			int len = snprintf(buf, 50, "na linha %d encontrado %d vezes\n", WEXITSTATUS(status), found_V[i]);
			write(1, buf, len);
    	}
	}
	close(pd[0]);
    return 0;
    
}


// ex.6
void linesWithValue(int **matrix, int value) {

    // TO DOm
}
