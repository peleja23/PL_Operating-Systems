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

void add(int fd, INFO* info){
	int registo = 0;
	registo = lseek(fd, 0, SEEK_END);
	registo = (registo / sizeof(INFO));
	write(fd, info, sizeof(INFO));
	printf("registo: %d \n",registo);
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
			lseek(fd, i*sizeof(temp), SEEK_SET);
			temp.idade = n_idade;
			write(fd, &temp, sizeof(INFO));
		}
		i++;
	}
}

void update_o(int fd, int registo, int n_idade){
	INFO temp;
	int bytes_read;
	int i = 0;
	while((bytes_read = read(fd, &temp, sizeof(INFO)))>0){
		if(i == registo){
			lseek(fd, registo*sizeof(INFO), SEEK_SET);
			temp.idade = n_idade;
			write(fd, &temp, sizeof(INFO));
			_exit(0);
		}
		i++;
	}
}

int main(int argc, char* argv[]){
	int fd = open("informacao.bin", O_RDWR|O_CREAT, 0666);
	
		if(strcmp(argv[1],"-i") == 0){	
			strcpy(info.nome,argv[2]);
			info.idade=atoi(argv[3]);
			add(fd,&info);
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
			
		}else if(strcmp(argv[1],"-o") == 0){
			int registo = atoi(argv[2]);
			int n_idade = atoi(argv[3]);
			update_o(fd, registo, n_idade);
			close(fd);
			return 0;
		}
	return 0;
}
