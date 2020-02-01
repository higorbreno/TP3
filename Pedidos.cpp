#pragma warning(disable : 4996)

#include <fstream>
#include <iostream>
#include "Menu.h"
#include "Vetor.h"
#include "Pedidos.h"
using namespace std;

extern estoque* vetor;
extern int tamanhoUsado;

void lerPedido(char* arquivo) {
	ifstream fin;

	fin.open(arquivo);

	char empresa[50];
	fin.getline(empresa, 50);
	char ch;
	do {
		fin.get(ch);
	} while (ch != '\n');

	bool primeiraFalha = false;

	pedido Pedido;
	pedido* pedidos = new pedido[tamanhoUsado];
	int quantidadePedidos = 0;
	int i = 0;

	do {
		fin >> Pedido.nome;
		formatarNome(Pedido.nome);
		fin >> Pedido.quantidade;
		bool existe = false;
		for (int j = 0; j < i + 1 && !existe; ++j) {
			if (!strcmp(pedidos[j].nome, Pedido.nome)) {
				pedidos[j].quantidade += Pedido.quantidade;
				existe = true;
			}
		}
		if (!existe) {
			pedidos[i++] = Pedido;
			++quantidadePedidos;
		}
		
	} while (!fin.eof());

	int falhas = 0;

	for (int j = 0; j < i; ++j) {
		Pedido = pedidos[j];
		int quantidadeFalta = checarEstoque(Pedido);

		

		if (quantidadeFalta && !primeiraFalha) {
			primeiraFalha = true;
			cout << "\nPedido falhou!\n";
			cout << Pedido.nome << ": Solicitado = " << Pedido.quantidade << "kg / Em estoque = " << Pedido.quantidade - quantidadeFalta << "kg\n";
		}
		else if (quantidadeFalta) {
			cout << Pedido.nome << ": Solicitado = " << Pedido.quantidade << "kg / Em estoque = " << Pedido.quantidade - quantidadeFalta << "kg\n";
			++falhas;
		}
	}

	if (falhas) {
		system("pause");
		return;
	}
	else {
		gerarNota(arquivo, empresa, pedidos, quantidadePedidos);
	}

	delete[] pedidos;
	fin.close();
}

int checarEstoque(pedido pedido) {
	bool achou = false;
	for (int i = 0; i < tamanhoUsado && !achou; ++i) {
		if (!strcmp(vetor[i].nome, pedido.nome)) {
			if (pedido.quantidade > vetor[i].quantidade) {
				return pedido.quantidade - vetor[i].quantidade;
				achou = true;
			}
		}
	}
	return 0;
}

void gerarNota(char* arquivo, char* empresa, pedido* pedidos, int quantidade) {
	int indice = strlen(strtok(arquivo, ".")) + 1;
	arquivo[indice++] = 'n';
	arquivo[indice++] = 'f';
	arquivo[indice] = 'c';

	ofstream fout;

	fout.open(arquivo);

	fout << empresa << endl;
	fout << "--------------------------------------\n";
	fout.setf(ios_base::fixed, ios_base::floatfield);
	fout.precision(2);
	float precoTotal = 0;
	for (int i = 0; i < quantidade; ++i) {
		fout << pedidos[i].nome << ": " << pedidos[i].quantidade << "kg a R$";
		for (int j = 0; j < tamanhoUsado; ++j) {
			if (!strcmp(pedidos[i].nome, vetor[j].nome)) {
				vetor[j].quantidade -= pedidos[i].quantidade;
				fout << vetor[j].preco << "/kg = R$" << vetor[j].preco * pedidos[i].quantidade << endl;
				precoTotal += vetor[j].preco * pedidos[i].quantidade;
			}
		}
	}
	fout << "--------------------------------------\n";
	fout << "Compra = R$" << precoTotal << endl;
	float desconto = 0;
	if (precoTotal > 1000) {
		desconto = precoTotal / 10;
	}
	fout << "Desconto = R$" << desconto << endl;
	fout << "Total = R$" << precoTotal - desconto;

	fout.close();
}