#include <iostream>
#include <fstream>
#include <cctype>
#include "Menu.h"
#include "Vetor.h"
#include "Pedidos.h"
using namespace std;

estoque* vetor;
int tamanhoVetor;
int tamanhoUsado;

void Menu(char* arquivo) {
	bool condicao = true;
	while (condicao) {
		system("cls");
		cout << "Sistema de Controle\n"
			<< "===================\n"
			<< "(P)edir\n"
			<< "(A)dicionar\n"
			<< "(E)xcluir\n"
			<< "(L)istar\n"
			<< "(S)air\n"
			<< "===================\n"
			<< "Opção: [ ]\b\b";

		char ch;
		cin >> ch;

		int n = 0;

		switch (toupper(ch)) {
		case 'P':
			Pedir();
			break;
		case 'A':
			n = Adicionar(n);
			break;
		case 'E':
			Excluir();
			break;
		case 'L':
			Listar();
			break;
		case 'S':
			condicao = !Sair(arquivo);
			break;
		}
	}
}

char* receberEstoque() {
	cout << "Digite o nome do arquivo do estoque: ";
	static char arquivo[50];
	cin.getline(arquivo, 50);

	ifstream fin;

	fin.open(arquivo, ios_base::binary);
	if (!fin.is_open()) {
		vetor = new estoque[0];
	}
	else {
		int tam;
		fin.read((char*)& tam, sizeof(int));

		tamanhoUsado = tam;
		tamanhoVetor = tam;
		vetor = new estoque[tam];

		for (int i = 0; i < tam; ++i) {
			fin.read((char*) &vetor[i], sizeof(estoque));
			formatarNome(vetor[i].nome);
		}

		fin.close();
	}
	return arquivo;
}

void Pedir() {
	system("cls");
	char arquivo[50];
	cout << "Pedir\n";
	cout << "-----\n";
	cout << "Arquivo: ";
	cin.ignore();
	cin.getline(arquivo, 50);

	lerPedido(arquivo);
}

int Adicionar(int n) {
	system("cls");
	system("chcp 1252 > nul");

	estoque produto;

	cout << "Adicionar\n";
	cout << "---------\n";
	cout << "Produto: ";
	cin.ignore();
	cin.getline(produto.nome, 20);
	formatarNome(produto.nome);
	cout << "Preço: ";
	cin >> produto.preco;
	cout << "Quantidade: ";
	cin >> produto.quantidade;

	bool diferente = true;
	for (int i = 0; i < tamanhoUsado && diferente; ++i) {
		diferente = strcmp(vetor[i].nome, produto.nome);
		if (!diferente) {
			vetor[i].preco = produto.preco;
			vetor[i].quantidade += produto.quantidade;
			return n;
		}
	}
	
	if (tamanhoUsado < tamanhoVetor) {
		vetor[tamanhoUsado++] = produto;
		return n;
	}

	int indice = tamanhoVetor;
	n = expandirVetor(n);

	vetor[tamanhoUsado++] = produto;
	return n;
}

void Excluir() {
	system("cls");
	cout << "Excluir\n";
	cout << "-------\n";

	int i = 0;
	while (i < tamanhoUsado) {
		cout << i << ") " << vetor[i++].nome << endl;
	}

	cout << endl << "Numero do produto: ";
	int produto;
	cin >> produto;
	--produto;
	
	cout << "Deseja excluir \"" << vetor[produto].nome << "\" (S/N)? ";
	char ch;
	cin >> ch;
	--i;
	if (toupper(ch) == 'S') {
		strcpy_s(vetor[produto].nome, vetor[i].nome);
		vetor[produto].preco = vetor[i].preco;
		vetor[produto].quantidade = vetor[i].quantidade;
		--tamanhoUsado;
	}
}

void Listar() {
	system("cls");
	cout << "Listagem\n";
	cout << "--------\n";

	cout.setf(ios_base::fixed, ios_base::floatfield);
	cout.precision(2);


	for (int i = 0; i < tamanhoUsado; ++i) {
		cout << vetor[i].nome << " - R$" << vetor[i].preco << " - " << vetor[i].quantidade << "kg\n";
	}
	system("pause");
}

bool Sair(char* arquivo) {
	ofstream fout;

	fout.open(arquivo, ios::binary);
	
	fout.write((char*) &tamanhoUsado, sizeof(int));

	for (int i = 0; i < tamanhoUsado; ++i) {
		fout.write((char*)& vetor[i], sizeof(estoque));
	}

	fout.close();

	return true;
}