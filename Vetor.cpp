#include <cctype>
#include <cmath>
#include "Menu.h";

extern estoque* vetor;
extern int tamanhoVetor;

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

int expandirVetor(int n) {
	estoque* temp = new estoque[tamanhoVetor];
	for (int i = 0; i < tamanhoVetor; ++i) {
		temp[i] = vetor[i];
	}
	delete[] vetor;

	int tamanhoAntigo = tamanhoVetor;
	tamanhoVetor += pow(2, n++);

	vetor = new estoque[tamanhoVetor];
	for (int i = 0; i < tamanhoAntigo; ++i) {
		vetor[i] = temp[i];
	}
	delete[] temp;
	return n;
}