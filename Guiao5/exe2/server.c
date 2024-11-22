#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include "defs.h"
#include "vector.h"

//FIFO criado pelo servidor
//Cliente pode receber um sigpipe (concorrência!)

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
	int fdl;
	char str_pid[10];
	Msg msg;
	int bytes_read;
	char buf[4];
	
	init_vector();
	print_vector();
		
	create_fifo(argv[1]);
	fdl = open("log.txt", O_WRONLY | O_CREAT, 0666);
	if(fdl < 0){
		perror("open");
		return -1;
	}
	fd = open(argv[1], O_RDONLY);	
	while((bytes_read = read(fd, &msg, sizeof(Msg))) > 0){	
		
		//search for the needle
		msg.occurrences = count_needle(msg.needle);

		snprintf(str_pid, sizeof(str_pid), "%d", msg.pid);
		
		snprintf(buf, sizeof(buf), "%d", msg.occurrences);
		
		//testing
		write(fdl, &buf, sizeof(int));
		
		close(fdl);
		fda = open(str_pid, O_WRONLY);
		if(fda < 0){
			perror("open");
			return -1;
		}
		
		//send answer
		write(fda, &msg, sizeof(Msg));
		fd = open(argv[1], O_RDONLY);
		close(fda);

		
	}
	close(fd);
	return 0;
}
