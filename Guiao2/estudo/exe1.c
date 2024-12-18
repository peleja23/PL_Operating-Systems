#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h> 
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
	char buf[40];
	int meu_pid = getpid();
	int pid_pai = getppid();
	int len = snprintf(buf, 40, "o meu pid: %d \npid do pai: %d \n", meu_pid, pid_pai);
	write(1, buf, len);
	
	return 0;
}
