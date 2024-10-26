#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){

	int status;
	
	for(int i = 0; i<5 ; i++){
	
		if(fork() == 0){
			//execl("/bin/ls" ,"ls" ,"-l" ,NULL);
			execlp("ls" ,"ls" ,NULL);
			//execl("teste" ,"teste" ,"1" ,NULL);
			
			perror("execl:");
			_exit(1);
		}
	}
	for(int i = 0; i<5 ; i++){
	
		int terminado_pid = wait(&status);
		
		if(WIFEXITED(status)){
			printf("executou ls o pid: %d com codigo de saida: %d \n", terminado_pid, status);
		}
		
	}
	
return 0;
}
