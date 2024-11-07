#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
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
	int result;
	char str_pid[10];
	Msg msg;
	
	init_vector();
	print_vector();
		
	create_fifo(argv[1]);
	
	while(1){
		fd = open(argv[1], O_RDONLY);	
		//receive request	
		read(fd, &msg, sizeof(Msg));
		result = count_needle(msg.needle);
		msg.occurrences = result;
		printf("o resultado é: %d para o processo: %d\n", msg.occurrences, msg.pid);
		close(fd);
		snprintf(str_pid, sizeof(str_pid), "%d", msg.pid);
		fda = open(str_pid, O_WRONLY);
		if(fda < 0){
			perror("open");
			return -1;
		}
		//send answer
		write(fda, &msg, sizeof(Msg));
		close(fda);
	}
	
	return 0;
}
