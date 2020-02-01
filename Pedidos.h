// Arquivo .h que contém a definição do registro pedido e as funções da biblioteca Pedidos.h

#ifndef PEDIDOS
#define PEDIDOS

struct pedido {
	char nome[20];
	float quantidade;
};

void lerPedido(char*);
int checarEstoque(pedido);
void gerarNota(char*, char*, pedido*, int);

#endif