#include "matrix.h"
#include <string.h>


int main(int argc, char *argv[]) {

    // generate random matrix
    int **matrix = createMatrix();
	int value = atoi(argv[2]);
	int found;
    // print matrix
    printMatrix(matrix);
    
    if(strcmp(argv[1],"-ve") == 0){
		found = valueExists(matrix,value);
		if(found == 0){
			printf("o valor existe\n");
		}
		return 0;
	}
    else if(strcmp(argv[1],"-lw") == 0){
		linesWithValue(matrix,value);
		return 0;
	}

    // free matrix
    for (int i = 0; i < ROWS; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
