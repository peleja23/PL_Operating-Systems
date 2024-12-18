#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
	int pd[2];
	int pd1[2];
	int pd2[2];
	pipe(pd);
	
	if(fork() == 0){
		close(pd[0]);
		
		dup2(pd[1],1);
		close(pd[1]);
		
		execlp("grep", "grep", "-v", "^#", "/etc/passwd", NULL);
		_exit(1);
	}
	close(pd[1]);

	pipe(pd1);
	
	if(fork() == 0){
		close(pd1[0]);
		
		dup2(pd[0],0);
		close(pd[0]);
		dup2(pd1[1],1);
		close(pd1[1]);
		
		execlp("cut", "cut", "-f7", "-d:", NULL);
		_exit(1);
	}
	
	close(pd[0]);
	close(pd1[1]);
	
	pipe(pd2);
	
	if(fork() == 0){
		close(pd2[0]);
		dup2(pd1[0],0);
		close(pd1[0]);
		dup2(pd2[1],1);
		close(pd2[1]);
		
		execlp("uniq", "uniq", NULL);
		_exit(1);
	}
	close(pd1[0]);
	close(pd2[1]);
	
	if(fork() == 0){
		dup2(pd2[0],0);
		close(pd2[0]);
		
		execlp("wc", "wc", "-l", NULL);
		_exit(1);
	}
	
	close(pd2[0]);
	
	for(int i = 0; i<4; i++){
		wait(NULL);
	}
	
return 0;
}

