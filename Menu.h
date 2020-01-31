

#ifndef MENU
#define MENU

struct estoque {
	char nome[20];
	float preco;
	unsigned quantidade;
};

void receberEstoque();
void Menu();
int Adicionar(int);
void Excluir();
void Listar();
void Sair();

#endif