// Arquivo .h que contém a definição do registro estoque e as funções da biblioteca Menu.h

#ifndef MENU
#define MENU

struct estoque {
	char nome[20];
	float preco;
	int quantidade;
};

void receberEstoque();
void Menu();
void Pedir();
int Adicionar(int);
void Excluir();
void Listar();
bool Sair();

#endif