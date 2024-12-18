#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int exec_command(char* arg){

	//Estamos a assumir numero maximo de argumentos
	char *exec_args[10];

	char *string;	
	int exec_ret = 0;
	int i=0;

	char* command = strdup(arg);

	string=strtok(command," ");
	
	while(string!=NULL){
		exec_args[i]=string;
		string=strtok(NULL," ");
		i++;
	}

	exec_args[i]=NULL;
	
	exec_ret=execvp(exec_args[0],exec_args);
	
	return exec_ret;
}

int main(int argc, char* argv[]){
	int pd[3][2];
	char *commands[] = {
		"grep -v ^# /etc/passwd NULL",
		"cut -f7 -d:  NULL",
		"uniq NULL",
		"wc -l NULL"
	};
	int pids[4];
	
	for (int i = 0; i < 4; i++){
		if((pids[i] = fork()) == 0){
			if(i == 0){
				pipe(pd[i]);
				close(pd[i][0]);
				dup2(pd[i][1],1);
				close(pd[i][1]);
				exec_command(commands[i]);
				_exit(1);
			}
			if(i == 3){
				pipe(pd[i]);
				close(pd[i][1]);
				dup2(pd[i][0],0);
				close(pd[i][0]);
				exec_command(commands[i]);
				_exit(1);
			}
			pipe(pd[i-1]);
			pipe(pd[i]);
			dup2(pd[i-1][0],0);
			close(pd[i-1][0]);
			dup2(pd[i][1],1);
			close(pd[i][1]);
			exec_command( commands[i]);
			_exit(1);
		}
	}
	for(int i = 0; i < 4; i++){
		waitpid(pids[i], NULL, 0);
	}
return 0;
}		

