

#ifndef MENU
#define MENU

struct estoque {
	char nome[20];
	float quantidade;
	float preco;
	bool existe = true;
};

void receberEstoque();
int Adicionar(int);
void Excluir();
void Listar();


#endif