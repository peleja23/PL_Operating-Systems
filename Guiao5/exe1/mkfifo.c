#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){

	char *myfifo = argv[1];
	int fifo;
	fifo = mkfifo(myfifo, 0777);

	if(fifo < 0){
		perror("mkfifo");
		return -1;
	}

	return 0;
}
