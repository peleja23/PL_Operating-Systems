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
	int a[20];
	int i = 0;
	
	if(fork()==0){
		int b[] = {2, 1, 3, 6};
		printf("espera ....\n");
		write(pd[1], &b, sizeof(b));
		printf("enviei os numeros\n");
		close(pd[1]);
		_exit(0);
	}
	
	while((read(pd[0], a, sizeof(a))) > 0){
		printf("recebi o numero:%d \n",a[i]);
	}
	close(pd[0]);
	pid_filho = wait(&status);
	if(WIFEXITED(status)){
		printf("o filho %d enviou os seguinte numeros:\n", pid_filho);
		for (int i = 0; i < 4; i++) {
			printf("%d\n", a[i]);
		}
		
	}
}
