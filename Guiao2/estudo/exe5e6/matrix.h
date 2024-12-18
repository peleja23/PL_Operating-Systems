#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_RAND 10
#define ROWS 8
#define COLUMNS 14



int **createMatrix();

void printMatrix(int **matrix);

// ex.5
int valueExists(int **matrix, int value);

// ex.6
void linesWithValue(int **matrix, int value);
