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

void numberPerLine(int **matrix, int value, int *found){
	INFO info;
	int status;
	int pids[ROWS];
	int pd[2];
	pipe(pd);
	// fazer struct para passar a info com nr da linha e numero de vezes encontrada
    for(int i=0; i < ROWS; i++){
    	if(fork() == 0){
    		close(pd[0]);
    		info.num_linha = i;
    		info.vezes = 0;  
    		for(int j = 0; j < COLUMNS; j++){
    			if(matrix[i][j] == value){
    				info.vezes ++;
    			}
    		}
			if(info.vezes > 0){
				write(pd[1], &info, sizeof(INFO));
				close(pd[1]);
	    		_exit(0);
        	}
    		_exit(-1);
    	}
    }
	for(int i = 0; i < ROWS; i++){
		close(pd[1]);
		waitpid(pids[i], &status, 0);
		int exit_code = WEXITSTATUS(status);
		if(WIFEXITED(status)){
			if(exit_code == 0){
				read(pd[0], &info, sizeof(INFO));
				printf("na linha %d, aparecem %d vezes\n", info.num_linha, info.vezes);
			}else{
				printf("não foi encontrado na linha:%d",i);
			}		
		}
	}
	close(pd[0]);
}





