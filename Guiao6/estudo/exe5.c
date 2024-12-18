#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
	int pd[2];
	pipe(pd);
	
	if(fork() == 0){
		close(pd[0]);
		dup2(pd[1], 1);
		close(pd[1]);
		execlp("ls", "ls", "/etc", NULL);
		perror("execlp");
		_exit(1);
	}
	
	close(pd[1]);
	
	if(fork() == 0){
		close(pd[1]);
		dup2(pd[0], 0);
		close(pd[0]);
		execlp("wc", "wc", "-l", NULL);
		perror("execlp");
		_exit(1);
	}
	
	close(pd[0]);
	for(int i = 0; i < 2; i++){
		wait(NULL);
	}
}





