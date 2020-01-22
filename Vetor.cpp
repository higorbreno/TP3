#include <cctype>

void formatarNome(char* nome) {
	if (nome[0] != '\0') {
		toupper(nome[0]);
	}
	else {
		return;
	}
	int i = 1;
	while (nome[i] != '\0') {
		tolower(nome[i++]);
	}
}