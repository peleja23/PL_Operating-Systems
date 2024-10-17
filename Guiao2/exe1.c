#include <unistd.h> 
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char* argv[]){

	printf("Processo:%d\n", getpid());
	printf("Processo pai:%d\n", getppid());

	return 0;
}
