#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h> 
#include <string.h>

typedef struct{
	char nome[20];
	int  idade;	
}INFO;

INFO info;

void add(int fd, char* nome, int idade){
	lseek(fd, 0, SEEK_END);
	strcpy(info.nome,nome);
	info.idade = idade;
	write(fd, &info, sizeof(INFO));
}

void list(int fd, int N) {
	INFO temp;
	for (int i = 0; i < N; i++) {
		if (read(fd, &temp, sizeof(INFO)) > 0) {
			printf("Nome: %s, Idade: %d\n", temp.nome, temp.idade);
		}
	}
}

void update(int fd, char* nome, int n_idade){
	INFO temp;
	int bytes_read;
	int i = 0;
	while((bytes_read = read(fd, &temp, sizeof(INFO)))>0){
		if (strcmp(nome,temp.nome) == 0) {
			lseek(fd, i*sizeof(INFO), SEEK_SET);
			temp.idade = n_idade;
			write(fd, &temp, sizeof(INFO));
		}
	i++;
	}
}

int main(int argc, char* argv[]){
	int fd = open("informacao.bin", O_RDWR|O_CREAT, 0666);
	
		if(strcmp(argv[1],"-i") == 0){	
			char nome[20];
			strcpy(nome,argv[2]);
			int idade = atoi(argv[3]);
			add(fd, nome, idade);
			close(fd);
			return 0;
			
		}else if(strcmp(argv[1],"-l") == 0){
			int N = atoi(argv[2]);
			list(fd, N);
			close(fd);
			return 0;
			
		}else if(strcmp(argv[1],"-u") == 0){
			char nome[20];
			strcpy(nome,argv[2]);
			int n_idade = atoi(argv[3]);
			update(fd, nome, n_idade);
			close(fd);
			return 0;
			
		}
	return 0;
}
