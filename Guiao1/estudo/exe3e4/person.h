typedef struct pessoa{
	char nome[10];
	int  idade;	
}pessoa;

int add(char* nome, char* idade);

int list(char* qntdd);

int update(char* nome, char* idade);

int update_o(char* registo, char* idade);
