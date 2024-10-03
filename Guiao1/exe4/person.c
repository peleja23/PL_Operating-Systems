#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h> 
#include <string.h>
#include "person.h"


int add(char* nome, int idade){
	int fd = open("informacao.bin", O_RDWR|O_CREAT, 0666);
	if(fd < 0){
		perror("open");
		return 1;
	}
	
	INFO info;
	int registo = 0;
	registo = lseek(fd, 0, SEEK_END);
	registo = (registo / sizeof(INFO));
	strcpy(info.nome,nome);
	info.idade = idade;
	write(fd, &info, sizeof(INFO));
	
	return registo;
}

int list(int N) {
	int fd = open("informacao.bin", O_RDWR|O_CREAT, 0666);
	if(fd < 0){
		perror("open");
		return 1;
	}
	
	INFO info;
	for (int i = 0; i < N; i++) {
		if (read(fd, &info, sizeof(INFO)) > 0) {
			printf("Nome: %s, Idade: %d\n", info.nome, info.idade);
		}
	}
	return 0;
}

int update(char* nome, int n_idade){
	int fd = open("informacao.bin", O_RDWR|O_CREAT, 0666);
	if(fd < 0){
		perror("open");
		return 1;
	}
	
	INFO info;
	int bytes_read;
	while((bytes_read = read(fd, &info, sizeof(INFO)))>0){
		if (strcmp(nome,info.nome) == 0) {
			lseek(fd, -sizeof(INFO), SEEK_CUR);
			info.idade = n_idade;
			write(fd, &info, sizeof(INFO));
		}
	}
	return 0;
}

int update_o(int registo, int n_idade){
	int fd = open("informacao.bin", O_RDWR|O_CREAT, 0666);
	if(fd < 0){
		perror("open");
		return 1;
	}
	
	INFO info;
	lseek(fd, registo*sizeof(INFO), SEEK_SET);
	read(fd, &info, sizeof(INFO));
	info.idade = n_idade;
	lseek(fd, -sizeof(INFO), SEEK_CUR);
	write(fd, &info, sizeof(INFO));
	
	return 0;
	
}

