#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int system_my(const char* command){
	int status;
	int res;
	char *exec_args[20];
	int i = 0;
	
	
	exec_args[i] = NULL;
	
	if(fork() == 0){
		//execl("/bin/ls" ,"ls" ,"-l" ,NULL);
		execvp( , exec_args);
		
		perror("execvp:");
		_exit(-1);
	
	}
	
	res = wait(&status);
	
	if(WIFEXITED(status)){
		if(WEXITSTATUS(status) != -1){
		
			return WEXITSTATUS(status);
			
		}else{
			return -1
		}
	}
return -1;
}
