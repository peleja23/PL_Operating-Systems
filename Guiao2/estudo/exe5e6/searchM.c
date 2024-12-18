#include "matrix.h"


int main(int argc, char *argv[]) {

    // generate random matrix
    int **matrix = createMatrix();

    // print matrix
    printMatrix(matrix);
    int value = atoi(argv[2]);
	if(strcmp("-e", argv[1]) == 0){
		valueExists(matrix, value);
	}
	if(strcmp("-lw", argv[1]) == 0){
		linesWithValue(matrix, value);
	}
    // free matrix
    for (int i = 0; i < ROWS; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
