#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>


int main(int argc, char *argv[]){
	
	if(strcmp(argv[1],"1") == 0){
		printf("ola mundo \n");
		return 0;
		
	}else if (strcmp(argv[1],"2") == 0){
		printf("adeus mundo cruel \n");
		return 0;
	}

return 0;
}
