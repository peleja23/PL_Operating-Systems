#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h> 

int main(int argc, char* argv[]){
	int size = 10;
	char buf[size];
	int bytes_read;
	while((bytes_read = read(0, buf, size))>0){
		write(1, buf, bytes_read);
	}
return 0;
}

