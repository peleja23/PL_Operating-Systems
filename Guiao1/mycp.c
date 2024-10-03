#include <stdio.h>
#include <unistd.h>
#include <fcntl.h> 

int main(int argc, char* argv[]){
	int size = 100;
	char buf[size];
	
	int bytes_read;
	int fd = open(argv[1],O_RDONLY,0666);
	if(fd < 0){
		perror("open");
		return 1;
	}
	
	int fdw = open("copiado.txt",O_CREAT|O_WRONLY,0666);
	if(fdw < 0){
		perror("open");
		return 1;
	}
	
	while((bytes_read = read(fd,buf,size))>0){
		write(fdw,buf,bytes_read);
	}
	close(fd);
	close(fdw);
	return 0;
}
