#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int system_my(const char* command){
	int status;
	char *exec_args[20];
	int i = 0;
	int j = 0;
	char copy[10];
	strncpy(copy, command, 9);
	copy[9] = '\0';
	for (j = 0; copy[j] != '\0'; j++) {
		if (copy[j] == ' ') {
			j++;
		}
		exec_args[i++] = &copy[j];
		
		while (copy[j] != ' ' && copy[j] != '\0') {
			j++;
		}
		if (copy[j] != '\0') {
			copy[j] = '\0'; 
		}
    }
    
    exec_args[i] = NULL;
    
	if(fork() == 0){
		//execl("/bin/ls" ,"ls" ,"-l" ,NULL);
		execvp(exec_args[0] , exec_args);
		
		perror("execvp:");
		_exit(-1);
	
	}
	
	wait(&status);
	
	if(WIFEXITED(status)){
		if(WEXITSTATUS(status) != -1){
		
			return WEXITSTATUS(status);
			
		}else{
			return -1;
		}
	}
return -1;
}
