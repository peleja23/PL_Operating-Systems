#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "defs.h"

int create_fifo(char *name){
	int fifo;
	fifo = mkfifo(name, 0666);
	if(fifo < 0){
		perror("mkfifo");
		return -1;
	}
	return 0;
}

int main (int argc, char * argv[]){
	int fd;
	int fda;
	int request = atoi(argv[2]);
	int pid;
	char str_pid[10];
	Msg msg;
	pid = getpid();
	snprintf(str_pid, sizeof(str_pid), "%d", pid);
	create_fifo(str_pid);
	
	msg.needle = request;
	msg.pid = pid;
	msg.occurrences = 0;
	
	fd = open(argv[1],O_WRONLY);
	write(fd, &msg, sizeof(Msg));
	close(fd);
	
	fda = open(str_pid, O_RDONLY);
	if(fda < 0){
		perror("open");
		return -1;
	}
	int bytes_read = read(fda, &msg, sizeof(Msg));
	printf("li %d bytes.\n", bytes_read);
	close(fda);
	printf("o valor foi encontrado %d vezes.\n", msg.occurrences);
	
	return 0;
}

