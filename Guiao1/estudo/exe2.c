#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h> 

int main(int argc, char* argv[]){
	int size = 10;
	char buf[size];
	int bytes_read;
	int fd = open(argv[1], O_RDONLY, 0666);
	int fdcopy = open("./copiado.txt", O_CREAT|O_WRONLY, 0666);
	while((bytes_read = read(fd, buf, size))>0){
		write(fdcopy, buf, bytes_read);
	}
return 0;
}

