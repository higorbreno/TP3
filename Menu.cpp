#include <iostream>
#include <fstream>
#include <cctype>
#include "Menu.h"
#include "Vetor.h"
#include "Pedidos.h"
using namespace std;
const char estoq[] = "estoque.bin";

estoque* vetor;
int tamanhoVetor;
int tamanhoUsado;

//Função que mostra o menu principal e chama a função referente a opção desejada
void Menu() {
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
			condicao = !Sair();
			break;
		}
	}
}


//Função que pede um arquivo binário que contém o estoque inicial e guarda os produtos em um vetor dinâmico de tamanho igual a quantidade de produtos
void receberEstoque() {

	ifstream fin;

	fin.open(estoq, ios_base::binary);
	if (!fin.is_open()) {
		//Caso o arquivo não abra cria um vetor dinâmico vazio
		vetor = new estoque[0];
	}
	else {
		//Caso o arquivo abra lê a quantidade de produtos no estoque e guarda-os em um vetor dinâmico de tamanho igual aquantidade de produtos
		int tam;
		fin.read((char*) &tam, sizeof(int));

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


//Função que faz a solicitação de produtos e gera uma nota fiscal caso o pedido possa ser satisfeito
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


//Função que adiciona um novo produto ao vetor dinâmico
int Adicionar(int n) {
	system("cls");

	estoque produto;

	//Pede o nome, o preço e quantidade do produto novo
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


	//Checa se existe algum produto igual já disponível no estoque, caso sim, atualiza o preço e adiciona a quantidade
	bool diferente = true;
	for (int i = 0; i < tamanhoUsado && diferente; ++i) {
		diferente = strcmp(vetor[i].nome, produto.nome);
		if (!diferente) {
			vetor[i].preco = produto.preco;
			vetor[i].quantidade += produto.quantidade;
			return n;
		}
	}
	
	//Checa se o vetor já está lotado, caso não, coloca o produto na última posição
	if (tamanhoUsado < tamanhoVetor) {
		vetor[tamanhoUsado++] = produto;
		return n;
	}

	//Caso o vetor esteja lotado chama a função para aumentá-lo
	int indice = tamanhoVetor;
	n = expandirVetor(n);

	vetor[tamanhoUsado++] = produto;
	return n;
}


//Função que mostra uma lista enumerada dos produtos e exclui o produto escolhido, substituindo pelo produto na última posição para não ficar um espaço vazio no meio
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


//Função que lista os produtos com seus nomes, preços e quantidades
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


//Função que guarda os valores do vetor dinâmico no arquivo binário do estoque e sai do programa
bool Sair() {
	ofstream fout;

	fout.open(estoq, ios_base::binary);
	
	fout.write((char*) &tamanhoUsado, sizeof(int));

	for (int i = 0; i < tamanhoUsado; ++i) {
		fout.write((char*)& vetor[i], sizeof(estoque));
	}

	fout.close();

	return true;
}