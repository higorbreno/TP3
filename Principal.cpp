#include <iostream>
#include "Menu.h"
using namespace std;

int main() {
	char arquivo[50];
	strcpy_s(arquivo, receberEstoque());
	Menu(arquivo);

	return 0;
}