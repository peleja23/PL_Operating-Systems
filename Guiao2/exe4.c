#include <unistd.h> 
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char* argv[]){
	int status;
	for(int i = 0; i<=10; i++){
		pid_t pid;
		if((pid = fork())== 0){
			printf("no filho-> Processo:%d\n", getpid());
			printf("no filho-> Processo pai:%d\n", getppid());
			sleep(2);
			_exit(i+1);
		}
	}	
	for(int i = 0; i<=10; i++){
		int pid_terminou = wait(&status);
		int exit_code = WEXITSTATUS(status);
		if(WEXITSTATUS(status)){
			printf("terminou:%d, filho criado em:%d\n",pid_terminou, exit_code);
		}
	}
	
}
