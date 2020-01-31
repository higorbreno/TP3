#include <iostream>
#include <fstream>
#include <cctype>
#include "Menu.h"
#include "Vetor.h"
using namespace std;

estoque* vetor;
int tamanhoVetor;

void receberEstoque() {
	cout << "Digite o nome do arquivo do estoque: ";
	char arquivo[50];
	cin.getline(arquivo, 50);

	ifstream fin;

	fin.open(arquivo);
	if (!fin.is_open) {
		vetor = new estoque[0];
	}
	else {
		char ch;
		int linhas = 1;
		do {
			fin.get(ch);
			if (ch == '\n') {
				++linhas;
			}
		} while (!fin.eof());
		fin.close();

		tamanhoVetor = linhas;
		vetor = new estoque[linhas];

		fin.open(arquivo);
		if (!fin.is_open) {
			cout << "Erro na leitura do arquivo!\n";
			exit(EXIT_FAILURE);
		}

		for (int i = 0; i < linhas; ++i) {
			fin >> vetor[i].nome >> vetor[i].quantidade >> vetor[i].preco;
			formatarNome(vetor[i].nome);
		}

		fin.close();
	}
}

int Adicionar(int n) {
	system("cls");
	system("chcp 1252 > nul");
	cout << "Adicionar\n";
	cout << "---------\n";
	cout << "Produto: ";
	char produto[20];
	cin.getline(produto, 20);
	formatarNome(produto);
	cout << "Preço: ";
	float preco;
	cin >> preco;
	cout << "Quantidade: ";
	float quantidade;
	cin >> quantidade;

	for (int i = 0, bool diferente = true; i < tamanhoVetor && diferente; ++i) {
		diferente = !strcmp(vetor[i].nome, produto);
		if (!diferente) {
			vetor[i].preco = preco;
			vetor[i].quantidade += quantidade;
			return n;
		}
	}

	for (int i = 0, bool espaço = false; i < tamanhoVetor && !espaço; ++i) {
		espaço = !vetor[i].existe;
		if (espaço) {
			strcpy(vetor[i].nome, produto);
			vetor[i].preco = preco;
			vetor[i].quantidade = quantidade;
			return n;
		}
	}

	int indice = tamanhoVetor;
	n = expandirVetor(n);

	strcpy(vetor[indice].nome, produto);
	vetor[indice].preco = preco;
	vetor[indice].quantidade = quantidade;
	return n;
}

void Excluir() {
	system("cls");
	cout << "Excluir\n";
	cout << "-------\n";

	int i = 0;
	while (vetor[i].existe && i < tamanhoVetor) {
		cout << i + 1 << ") " << vetor[i++].nome << endl;
	}

	cout << endl << "Numero do produto: ";
	int produto;
	cin >> produto;
	--produto;
	
	cout << "Deseja excluir \"" << vetor[produto].nome << "\" (S/N)? ";
	char ch;
	cin >> ch;
	if (toupper(ch) == 'S') {
		strcpy(vetor[produto].nome, vetor[i].nome);
		vetor[produto].preco = vetor[i].preco;
		vetor[produto].quantidade = vetor[i].quantidade;
		vetor[i].existe = false;
	}
}

void Listar() {
	system("cls");
	cout << "Listagem\n";
	cout << "--------\n";

	cout.setf(ios_base::fixed, ios_base::floatfield);
	cout.precision(2);

	int i = 0;
	while (vetor[i].existe) {
		cout << vetor[i].nome << " - R$" << vetor[i].preco << " - " << vetor[i].quantidade << "kg\n";
	}
}