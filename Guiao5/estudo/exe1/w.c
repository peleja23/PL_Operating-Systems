#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
	char buf[30];
	int bytes_read;
	int fd = open("./fifo", O_WRONLY);
	if(fd < 0){
		perror("open");
		return 1;
	}
	while((bytes_read = read(0, buf, 30))>0){
		write(fd, buf, bytes_read);
	}
	close(fd);
}
