#pragma warning(disable : 4996)

#include <fstream>
#include <iostream>
#include "Menu.h"
#include "Vetor.h"
#include "Pedidos.h"
using namespace std;

extern estoque* vetor;
extern int tamanhoUsado;


//Função para ler o arquivo do pedido
void lerPedido(char* arquivo) {
	ifstream fin;

	
	fin.open(arquivo);
	while (!fin.is_open()) {
		cout << "Arquivo inválido!\nPor favor, digite novamente: ";
		cin >> arquivo;
		fin.open(arquivo);
	}

	char empresa[50];
	fin.getline(empresa, 50);
	char ch;
	do {
		fin.get(ch);
	} while (ch != '\n');

	bool primeiraFalha = false;

	//Cria uma variável do tipo pedido e um vetor dinâmico do tamanho da quantidade de produtos existentes no estoque
	pedido Pedido;
	pedido* pedidos = new pedido[tamanhoUsado];
	int quantidadePedidos = 0;
	int i = 0;

	//Pega os pedidos e junta os pedidos do mesmo produto
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
	
	//Checa se os pedidos são possíveis e mostra os produtos que falharam
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


//Função que checa se a quantidade disponível de um certo produto é suficiente para a quantidade solicitada
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


//Função para gerar uma nota fiscal com o valor total
void gerarNota(char* arquivo, char* empresa, pedido* pedidos, int quantidade) {
	//Muda a extensão do arquivo para .nfc
	int indice = strlen(strtok(arquivo, ".")) + 1;
	arquivo[indice++] = 'n';
	arquivo[indice++] = 'f';
	arquivo[indice] = 'c';

	ofstream fout;

	//Abre/Cria o arquivo
	fout.open(arquivo);


	//Escreve o nome da empresa, a quantidade, o valor do pedido de produtos individuais e o valor da compra total
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

	//Aplica o desconto caso elegível
	float desconto = 0;
	if (precoTotal >= 1000) {
		desconto = precoTotal / 10;
	}
	fout << "Desconto = R$" << desconto << endl;
	fout << "Total = R$" << precoTotal - desconto;

	fout.close();
}