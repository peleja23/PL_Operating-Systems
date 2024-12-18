#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
	int pd[2];
	pipe(pd);
	int value = 5;
	int lido;
	char buf[20];
	if(fork() == 0){
		close(pd[1]);
		read(pd[0], &lido, sizeof(int));
		int len = snprintf(buf, 20, "valor: %d\n", lido);
		write(1, buf, len);
		close(pd[0]);
		_exit(1);
	}	
	close(pd[0]);	
	write(pd[1], &value, sizeof(int));
	wait(NULL);
	close(pd[1]);
	
}
