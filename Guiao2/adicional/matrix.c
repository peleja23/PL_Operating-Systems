#include "matrix.h"
#include <unistd.h> 
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> 


int **createMatrix() {

    // seed random numbers
    srand(time(NULL));
    int fd;
    fd = open("matriz.bin", O_CREAT|O_WRONLY|O_APPEND , 0666);
    printf("aqui esta o fd %d\n",fd);
    
    // Allocate and populate matrix with random numbers.
    printf("Generating numbers from 0 to %d...", MAX_RAND);
    int **matrix = (int **) malloc(sizeof(int*) * ROWS);
    for (int i = 0; i < ROWS; i++) {
        matrix[i] = (int*) malloc(sizeof(int) * COLUMNS);
        for (int j = 0; j < COLUMNS; j++) {
            matrix[i][j] = rand() % MAX_RAND;
            write(fd, matrix[i][j], sizeof(matrix[i][j]));
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
		if(WIFEXITED(status) && WEXITSTATUS(status) == 0){
			return 0;
		}
	}
	return 1;
}


// ex.6
void linesWithValue(int **matrix, int value) {
	int status;
	int pids[ROWS];
    for(int i=0; i < ROWS; i++){
    	if((pids[i] = fork()) == 0){
    		for(int j = 0; j < COLUMNS; j++){
    			if(matrix[i][j] == value){
    				_exit(i+1);
    			}
    		}
    		_exit(0);
    	}
    }
	for(int i = 0; i < ROWS; i++){
		waitpid(pids[i], &status, 0);
		int exit_code = WEXITSTATUS(status);
		if(WIFEXITED(status) && WEXITSTATUS(status) != 0){
			printf("o numero foi encontrado na linha %d\n", exit_code-1);
		}
	}
}



