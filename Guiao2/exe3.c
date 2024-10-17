#include <unistd.h> 
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char* argv[]){
	int status;
	
	for(int i = 0; i<=10; i++){
		if(fork() == 0){
			printf("no filho-> Processo:%d\n", getpid());
			printf("no filho-> Processo pai:%d\n", getppid());
			printf("%d\n", i); //duvida
			_exit(i+1);
		}
		int pid_terminou = wait(&status);
		if(WEXITSTATUS(status)){
			printf("terminou o processo %d ordem:%d\n", pid_terminou, status);
		}
	}
	
}
