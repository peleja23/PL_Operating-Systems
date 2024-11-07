#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>


int main(int argc, char *argv[]){
	int pd[2];
	pipe(pd);
	int status;
	int pid_filho;
	int a;
	
	if(fork()==0){
		close(pd[0]);
		for (int i = 0; i<16700; i++){		
			write(pd[1], &i, sizeof(int));
			printf("enviei o numero: %d\n", i);
		} 
		close(pd[1]);
		_exit(0);
	}
	
	close(pd[1]);
	sleep(5);
	while((read(pd[0], &a, sizeof(a)))>0){
		printf("numero recebido: %d\n", a);
	}
	close(pd[0]);
	pid_filho = wait(&status);
	if(WIFEXITED(status)){
		printf("o filho %d terminou\n", pid_filho);
		
	}
}
