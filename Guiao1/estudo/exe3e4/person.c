#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h> 
#include <fcntl.h>
#include "person.h"

int add(char* nome, char* c_idade){
	pessoa p;
	int idade = 0;
	char buf[20];
	idade = atoi(c_idade);
	int fd = open("./mou.bin", O_CREAT|O_WRONLY, 0666);
	if(fd == -1){
		perror("open");
		return 1;
	}
	strcpy(p.nome, nome);
	p.idade = idade;
	long registos = lseek(fd, 0, SEEK_END);
	write(fd, &p, sizeof(pessoa));
	close(fd);
	int len = snprintf(buf, 20, "registo: %ld \n", (registos/sizeof(pessoa))+1);
	write(1, buf, len);
	
	return 0;
}

int list(char* c_qntdd){
	pessoa p;
	char buf[20];
	int qntdd = atoi(c_qntdd);
	int fd = open("./mou.bin", O_RDONLY, 0666);
	if(fd == -1){
		perror("open");
		return 1;
	}
	for(int i = 0; i < qntdd; i++){
		read(fd, &p, sizeof(pessoa));
		int len = snprintf(buf, sizeof(buf), "%s -> %d \n", p.nome, p.idade);
		write(1, buf, len);
	}
	
	return 0;
}

int update(char* nome, char* c_idade){
	pessoa p;
	int idade = atoi(c_idade);
	int fd = open("./mou.bin", O_RDWR, 0666);
	if(fd == -1){
		perror("open");
		return 1;
	}
	while((read(fd, &p, sizeof(pessoa)))>0){
		if(strcmp(nome, p.nome) == 0){
			p.idade = idade;
			lseek(fd, -sizeof(pessoa), SEEK_CUR);
			write(fd, &p, sizeof(pessoa));
		}
	}
	
	return 0;
}

int update_o(char* c_registo, char* c_idade){
	pessoa p;
	int idade = atoi(c_idade);
	int registo = atoi(c_registo);
	int fd = open("./mou.bin", O_RDWR, 0666);
	if(fd == -1){
		perror("open");
		_exit(1);
	}
	lseek(fd, ((registo-1) * sizeof(pessoa)), SEEK_SET);
	read(fd, &p, sizeof(pessoa));
	p.idade = idade;
	lseek(fd, -sizeof(pessoa), SEEK_CUR);
	write(fd, &p, sizeof(pessoa));
	close(fd);
	
	return 0;
}








