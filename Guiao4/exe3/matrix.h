#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

#define MAX_RAND 10
#define ROWS 5
#define COLUMNS 10 

typedef struct{
	int	 num_linha;
	int  vezes;	
}INFO;

int **createMatrix();

void printMatrix(int **matrix);

// ex.5
int valueExists(int **matrix, int value);

// ex.6
void linesWithValue(int **matrix, int value);

// exe3 do guiao4
void numberPerLine(int **matrix, int value, int *found);
