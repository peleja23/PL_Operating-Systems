#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h> 
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
	char buf[50];
	int status;
	int meu_pid = getpid();
	int pid_pai;
	int len = snprintf(buf, 40, "pid do pai: %d\n", meu_pid);
	write(1, buf, len);
	
	for(int i = 0; i < 10; i++){
		if(fork() == 0){
			meu_pid = getpid();
			pid_pai = getppid();
			int len = snprintf(buf, 50, "	o meu pid: %d pid do meu pai: %d\n", meu_pid, pid_pai);
			write(1, buf, len);
			_exit(i+1);
		}
		wait(&status);
		if(WIFEXITED(status)){
			int len = snprintf(buf, 50, "codigo de saida do filho: %d\n", WEXITSTATUS(status));
			write(1, buf, len);
		}
	}
	return 0;
}
