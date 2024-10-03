typedef struct{
	char nome[20];
	int  idade;	
}INFO;
int add(char* nome, int idade);
int list(int N);
int update(char* nome, int n_idade);
int update_o(int registo, int n_idade);
