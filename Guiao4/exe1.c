#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>


int main(int argc, char *argv[]){
	int pd[2];
	pipe(pd); // falta verificar se correu tudo bem com if (pipe(pd)<0) e dps perror
	int status;
	int pid;
	int a = atoi(argv[1]);
	
	if(fork()==0){
		int b = 0;
		close(pd[1]);
		printf("espera....\n"); // perguntar ao stor
		read(pd[0], &b, sizeof(int));
		printf("recebi o numero: %d\n", b);
		close(pd[0]);
		_exit(b);
	}
	
	sleep(5);
	close(pd[0]);
	write(pd[1], &a, sizeof(int));
	close(pd[1]);
	pid = wait(&status);
	if(WIFEXITED(status)){
		printf("o filho %d recebeu o numero: %d\n", pid, WEXITSTATUS(status));
	}
}
