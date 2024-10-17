#include <unistd.h> 
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char* argv[]){
	int status;
	pid_t pid;

	if((pid = fork())== 0){
		printf("no filho-> Processo:%d\n", getpid());
		printf("no filho-> Processo pai:%d\n", getppid());
		_exit(0);
	}

	printf("no pai-> Processo:%d\n", getpid());
	printf("no pai-> Processo pai:%d\n", getppid());
	printf("no pai-> Processo filho:%d\n", pid);
	int terminado_pid = wait(&status);
	if(WIFEXITED(status)){
		printf("terminou %d com codigo de saida: %d \n", terminado_pid, status);
	}
	
	return 0;
}
