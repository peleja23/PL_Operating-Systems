#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
	int status;
	char buf[40];
	
	if(fork() == 0){
		execlp("ls", "ls", "-l", NULL);
		perror("execlp");
		_exit(1);
	}
	
	wait(&status);
	if(WIFEXITED(status) && WEXITSTATUS(status) != 1){
		int len = snprintf(buf, 40, "O exec funcionou corretamente\n");
		write(1, buf, len);
	}
	
	return 0;
}
