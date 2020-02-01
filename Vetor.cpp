#include <cctype>
#include <cmath>
#include "Menu.h";

extern estoque* vetor;
extern int tamanhoVetor;


// Fun��o que formata um vetor de caracteres para que fiquem com a primeira letra mai�scula e o resto min�scula
void formatarNome(char* nome) {
	if (nome[0] != '\0') {
		nome[0] = toupper(nome[0]);
	}
	else {
		return;
	}
	int i = 1;
	while (nome[i] != '\0') {
		nome[i++] = tolower(nome[i]);
	}
}


//Fun��o que expande o vetor
int expandirVetor(int n) {
	//Cria um vetor din�mico tempor�rio para guardar os produtos
	estoque* temp = new estoque[tamanhoVetor];
	for (int i = 0; i < tamanhoVetor; ++i) {
		temp[i] = vetor[i];
	}
	//Deleta o vetor din�mico para poder criar um novo vetor referente ao mesmo ponteiro
	delete[] vetor;

	//Cria o novo vetor com tamanho atualizado
	int tamanhoAntigo = tamanhoVetor;
	tamanhoVetor += pow(2, n++);
	vetor = new estoque[tamanhoVetor];

	//Guarda os produtos no novo vetor
	for (int i = 0; i < tamanhoAntigo; ++i) {
		vetor[i] = temp[i];
	}
	delete[] temp;
	return n;
}