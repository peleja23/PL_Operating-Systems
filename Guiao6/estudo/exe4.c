#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
	int pd[2];
	pipe(pd);
	int bytes_read;
	char buf[20];
	if(fork() == 0){
		close(pd[1]);
		dup2(pd[0], 0);
		close(pd[0]);
		execlp("wc", "wc", NULL);
		perror("execlp");
		_exit(1);
	}
	close(pd[0]);
	while((bytes_read = read(0, buf, 20)) > 0){
		write(pd[1], buf, bytes_read);
	}
	close(pd[1]);
	wait(NULL);

}




