#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h> 
#include <string.h>
#include "person.h"

int main(int argc, char* argv[]){
	
		if(strcmp(argv[1],"-i") == 0){	
			char nome[20];
			strcpy(nome,argv[2]);
			int idade = atoi(argv[3]);
			int registo = add(nome, idade);
			printf("registo: %d \n",registo);
			return 0;
			
		}else if(strcmp(argv[1],"-l") == 0){
			int N = atoi(argv[2]);
			list(N);
			return 0;
			
		}else if(strcmp(argv[1],"-u") == 0){
			char nome[20];
			strcpy(nome,argv[2]);
			int n_idade = atoi(argv[3]);
			update(nome, n_idade);
			return 0;
			
		}else if(strcmp(argv[1],"-o") == 0){
			int registo = atoi(argv[2]);
			int n_idade = atoi(argv[3]);
			update_o(registo, n_idade);
			return 0;
		}
		
	return 0;
}
