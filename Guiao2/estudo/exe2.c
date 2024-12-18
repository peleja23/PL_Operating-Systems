#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h> 
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
	int meu_pid = getpid();
	int pid_pai = getppid();
	int pid_filho;
	char buf[80];
	if((pid_filho = fork()) == 0){
		meu_pid = getpid();
		pid_pai = getppid();
		int len = snprintf(buf, 80, "no filho:\n	meu pid: %d\n	pid do pai: %d\n",meu_pid, pid_pai);
		write(1, buf, len);
		_exit(0);
	}
	wait(NULL);
	int len = snprintf(buf, 80, "no pai:\n	meu pid: %d\n	pid do pai: %d\n	pid do filho: %d\n", meu_pid, pid_pai, pid_filho);
	write(1, buf, len);
	
	return 0;
}
