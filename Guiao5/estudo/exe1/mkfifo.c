#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char* argv[]){

	if(mkfifo("./fifo",0666) < 0){
		perror("mkfifo");
		return 1;
	}
	
	return 0;
}
