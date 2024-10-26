#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "system_my.h"

int main(int argc, char *argv[]){

	char comando1[] = "ls";
	char comando2[] = "sleep 10";
	char comando3[] = "ps";
	char comando4[] = "ls -l -a";
	
	int res;
	res = system_my(comando1);
	printf("ao executar ls retornou com: %d \n", res);

	res = system_my(comando2);
	printf("ao executar sleep 10 retornou com: %d \n", res);
	
	res = system_my(comando3);
	printf("ao executar ps retornou com: %d \n", res);
	
	res = system_my(comando4);
	printf("ao executar ls -l -a retornou com: %d \n", res);

return 0;
}
