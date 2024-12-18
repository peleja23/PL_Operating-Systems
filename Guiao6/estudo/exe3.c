#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
	char buf[20];
	int fd = open("./etc/passwd", O_RDONLY, 0666);
	if(fd < 0){
		perror("open");
		return 1;
	}
	
	int fds = open("saida.txt", O_WRONLY|O_CREAT|O_TRUNC, 0666);
	if(fds < 0){
		perror("open");
		return 1;
	}
	
	int fde = open("erros.txt", O_WRONLY|O_CREAT, 0666);	
	if(fde < 0){
		perror("open");
		return 1;
	}
	
	dup2(fd, 0);
	close(fd);
	
	int nfd = dup(1);
	dup2(fds, 1);
	close(fds);
	
	dup2(fde, 2);
	close(fde);
	if(fork() == 0){
		execlp("wc", "wc", NULL);
		_exit(1);
	}
	wait(NULL);
	int len =  snprintf(buf, 20, "terminei\n");
	write(nfd, buf, len);
}
