

#ifndef MENU
#define MENU

struct estoque {
	char nome[20];
	float preco;
	unsigned quantidade;
};

char* receberEstoque();
void Menu();
int Adicionar(int);
void Excluir();
void Listar();
void Sair(char*);

#endif