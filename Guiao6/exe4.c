#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
	int status;
	int bytes_read;
	char buf[20];
	int pd[2]; 
	
	if (pipe(pd) == -1) {//perguntar ao stor pq é q o meu pipe so funciona se der init assim
		perror("pipe");
		return 1;
	}
	
	if(fork()==0){
		close(pd[1]);
		dup2(pd[0],0);
		close(pd[0]);
		execlp("wc", "wc", NULL);
		perror("execlp");
		_exit(1);
	}
	close(pd[0]);
	
	while((bytes_read = read(0, &buf, 20))>0){
		write(pd[1], &buf, bytes_read);
	}
	
	close(pd[1]);
	wait(&status);
	if(WIFEXITED(status) && WEXITSTATUS(status) != 1){
		return 0;
	}
	return 1;
}
