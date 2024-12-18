#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h> 
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
	int status;
	char buf[50];
	int meu_pid = getpid();
	
	int len = snprintf(buf, 50, "pid do pai: %d\n", meu_pid);
	write(1, buf, len);
	
	for(int i = 0; i < 10; i++){
		if(fork() == 0){
			meu_pid = getpid();
			int pid_pai = getppid();
			len = snprintf(buf, 50, "	meu pid: %d\n	pid do pai: %d\n\n", meu_pid, pid_pai);
			write(1, buf, len);
			_exit(i+1);
		}
	}
	
	for(int i = 0; i < 10; i++){
		wait(&status);
		if(WIFEXITED(status)){
			len = snprintf(buf, 50, "codigo de saida de um dos filhos %d\n", WEXITSTATUS(status));
			write(1, buf, len);
		}
	}
	
	return 0;
}
