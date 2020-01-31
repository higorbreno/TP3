#include <iostream>
#include <fstream>
#include <cctype>
#include "Menu.h"
#include "Vetor.h"
using namespace std;

estoque* vetor;
int tamanhoVetor;
int tamanhoUsado;

void Menu() {
	while (true) {
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
			//Pedir();
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
			Sair();
			break;
		}
	}
}

void receberEstoque() {
	cout << "Digite o nome do arquivo do estoque: ";
	char arquivo[50];
	cin.getline(arquivo, 50);

	ifstream fin;

	fin.open(arquivo);
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

	bool diferente = true;
	for (int i = 0; i < tamanhoVetor && diferente; ++i) {
		diferente = !strcmp(vetor[i].nome, produto);
		if (!diferente) {
			vetor[i].preco = preco;
			vetor[i].quantidade += quantidade;
			return n;
		}
	}
	
	if (tamanhoUsado < tamanhoVetor) {
		strcpy_s(vetor[++tamanhoUsado].nome, produto);
		vetor[tamanhoUsado].preco = preco;
		vetor[tamanhoUsado].quantidade = quantidade;
		return n;
	}
	

	int indice = tamanhoVetor;
	n = expandirVetor(n);

	strcpy_s(vetor[indice].nome, produto);
	vetor[indice].preco = preco;
	vetor[indice].quantidade = quantidade;
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

void Sair() {

	exit(EXIT_SUCCESS);
}