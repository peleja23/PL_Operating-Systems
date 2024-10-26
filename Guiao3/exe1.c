#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){

	//execl("/bin/ls" ,"ls" ,"-l" ,NULL);
	execl("./teste" ,"teste" ,"2" ,NULL);
	//execlp("ls" ,"ls" ,"-l" ,NULL);
	
	perror("execl falhou");

return 0;
}
