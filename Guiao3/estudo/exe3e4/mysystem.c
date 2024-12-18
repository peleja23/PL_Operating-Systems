#include "mysystem.h"


// recebe um comando por argumento
// returna -1 se o fork falhar
// caso contrario retorna o valor do comando executado
int mysystem (char* command) {
    int res = -1;
    int status;
    char* args[10];
    int i = 0;
    char* token = strtok(command, " ");
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL; 
	if(fork() == 0){
		execvp(args[0], args);
		perror("execvp");
		_exit(-1);
	}
	wait(&status);
	if(WIFEXITED(status)){
		res = WEXITSTATUS(status);
	}

	return res;
}
