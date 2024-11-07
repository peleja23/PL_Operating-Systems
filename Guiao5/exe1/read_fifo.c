#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h> 


int main(int argc, char *argv[]){
	int fd;
	char buf[100];
	int bytes_read;
	
	fd = open(argv[1], O_RDONLY);
	while((bytes_read = read(fd,buf,100))>0){
		write(1,buf,bytes_read);
	}
	close(fd);
	
return 0;
}

