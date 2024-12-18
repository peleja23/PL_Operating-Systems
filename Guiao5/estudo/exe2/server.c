#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "defs.h"
#include "vector.h"

//FIFO criado pelo servidor
//Cliente pode receber um sigpipe (concorrência!)

int main (int argc, char * argv[]){
	char buf[20];
	init_vector();
	print_vector();
	
	Msg m;
	if (mkfifo("./fifo", 0777)<0){
		perror("mkfifo");
		return 1;
	}
	int fd = open("fifo", O_RDONLY);
	while(1){
		while(read(fd, &m, sizeof(Msg)) > 0){
			read(fd, &m, sizeof(Msg));
			m.occurrences = count_needle(m.needle);
			snprintf(buf, 20, "fifo%d", m.pid);
			int fdans = open(buf, O_WRONLY);
			write(fdans, &m, sizeof(Msg));
			close(fdans);
		}
	}
	close(fd);	
	return 0;
}
