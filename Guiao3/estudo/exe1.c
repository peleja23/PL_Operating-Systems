#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]){

	execlp("ls", "ls", "-l", NULL);
	perror("execlp");
		
return 0;
}
