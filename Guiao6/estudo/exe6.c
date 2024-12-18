#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
	int pd[3][2];
	pipe(pd[0]);
	if(fork() == 0){
		close(pd[0][0]);
		dup2(pd[0][1], 1);
		close(pd[0][1]);
		execlp("grep", "grep", "-v", "^#", "/etc/passwd", NULL);
		perror("execlp");
		_exit(1);
	}
	close(pd[0][1]);
	pipe(pd[1]);
	if(fork() == 0){
		close(pd[1][0]);
		dup2(pd[0][0], 0);
		close(pd[0][0]);
		dup2(pd[1][1], 1);
		close(pd[1][1]);
		execlp("cut", "cut", "-f7", "-d:", NULL);
		perror("execlp");
		_exit(1);
	}
	close(pd[1][1]);
	pipe(pd[2]);
	if(fork() == 0){
		close(pd[2][0]);
		dup2(pd[1][0],0);
		close(pd[1][0]);
		dup2(pd[2][1], 1);
		close(pd[2][1]);
		execlp("uniq", "uniq", NULL);
		perror("execlp");
		_exit(1);
	}
	close(pd[2][1]);
	if(fork() == 0){
		dup2(pd[2][0], 0);
		close(pd[2][0]);
		execlp("wc", "wc", "-l", NULL);
		perror("execlp");
		_exit(1);
	}
	close(pd[2][0]);
	for (int i = 0; i<4; i++){
		wait(NULL);
	}
}




