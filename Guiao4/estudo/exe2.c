#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
	int value[] = {5, 4, 6 ,7 };
	int pd[2];
	pipe(pd);
	int lido;
	char buf[30];
	if(fork() == 0){
		close(pd[0]);
		for(int i = 0; i < 4; i++){
			write(pd[1], &value[i], sizeof(int));
		}
		close(pd[1]);
		_exit(0);
	}
	close(pd[1]);
	wait(NULL);
	while(read(pd[0], &lido, sizeof(int)) > 0){
		int len =  snprintf(buf, 30, "valor lido: %d\n", lido);
		write(1, buf, len);
	}
	close(pd[0]);
	
	return 0;
}
