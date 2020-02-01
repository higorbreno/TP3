

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