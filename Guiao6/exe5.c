#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
	int pd[2];
	pipe(pd);
	
	if(fork() == 0){
		close(pd[0]);
		dup2(pd[1],1);
		close(pd[1]);
		execlp("ls","ls","/etc",NULL);
		_exit(1);
	}
	close(pd[1]);
	if(fork() == 0){
		dup2(pd[0],0);
		close(pd[0]);
		execlp("wc","wc","-l",NULL);
		_exit(1);
	}
	close(pd[0]);
	wait(NULL);
	wait(NULL);
	
return 0;
}
