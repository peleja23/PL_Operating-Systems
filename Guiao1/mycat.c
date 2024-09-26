#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]){

	char buf[100];
	
	int bytes_read;

	while((bytes_read = read(0,buf,100))>0){
		write(1,buf,bytes_read);
	}
	return 0;
}
