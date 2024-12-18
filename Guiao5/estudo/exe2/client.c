#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "defs.h"

int main (int argc, char * argv[]){
	char buf[20];
	int value = atoi(argv[1]);
	int pid = getpid();
	Msg m;
	snprintf(buf, 20, "fifo%d", pid);
	if(mkfifo(buf, 0777)<0){
		perror("mkfifo");
		return 1;
	}
	int fd = open("fifo", O_WRONLY);
	if(fd < 0){
		perror("open");
		return 1;
	}	
	
	m.needle = value;
	m.pid = getpid();
	m.occurrences = 0;
	write(fd, &m, sizeof(Msg));
	close(fd);
	
	int fdans = open(buf, O_RDONLY);
	if(fdans < 0){
		perror("open");
		return 1;
	}
	while(read(fdans, &m, sizeof(Msg))>0){
		int len = snprintf(buf, 20, "ocorreu:%d\n", m.occurrences);
		write(1, buf, len);
	}
	close(fdans);
	return 0;
}

