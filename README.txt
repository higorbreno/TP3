# TP3

Sistema de gerência de pizzaria

Pizzeria's management system

O objetivo do projeto é criar um sistema de pedidos de produtos.
O programa pedirá o nome de um arquivo binário no começo do programa que estará guardado os produtos disponíveis no estoque.
	O arquivo terá um produto diferente em cada linha, que seguirá a ordem: nome, preço e quantidade.
	
	Pizzaria Mamute
	---------------
	massa 20
	queijo 5
	Massa 10
	frango 5
	molho 40
	Queijo 30
	FRANGO 10
	presunto 18
	
Os produtos serão passados para um vetor dinâmico de posições iguais a quantidade de produtos no arquivo.

Depois do arquivo ser processado e os produtos guardados no vetor dinâmico, aparecerá um menu com cinco opções:

	Sistema de Controle
	===================
	(P)edir
	(A)dicionar
	(E)xcluir
	(L)istar
	(S)air
	===================
	Opção: [_]

A opção (P)edir recebe um arquivo texto com o nome da empresa e os produtos solicitados.
	Primeiro, checa se a quantidade de cada um dos produtos do pedido estão disponíveis no estoque, se não falha o pedido e mostra quais produtos foram insuficientes.
	Segundo, se sim, é atualizado os produtos no estoque, e é gerado uma nota fiscal com o mesmo nome do arquivo do pedido com a extensão ".nfc", 
	que contém o nome da empresa, os produtos pedidos com seus preços e quantidades, o valor da compra total e desconto de 10% no caso de o valor total for maior que 1000 reais.
	
	Pizzaria Mamute
	--------------------------------------
	Massa: 30kg a R$2.50/kg = R$75.00
	Queijo: 35kg a R$15.00/kg = R$525.00
	Frango: 15kg a R$9.00/kg = R$135.00
	Molho: 40kg a R$8.20/kg = R$328.00
	Presunto: 18kg a R$10.00/kg = R$180.00
	--------------------------------------
	Compra = R$1243.00
	Desconto = R$124.30
	Total = R$1118.70

A opção (A)dicionar deve adicionar um novo produto ao vetor do estoque, e caso não tenha espaço, aumentar o vetor.
	O vetor dinâmico aumentará de tamanho, de forma que seu novo tamanho seja o tamanho anterior mais 2 elevado a n, sendo n a quantidade de vezes que o vetor foi expandido, iniciando no 0.

A opção (E)xcluir mostra uma lista enumerada dos nomes dos produtos disponíveis no estoque, começando do 1, onde a ordem não importa.
	Deve receber um número e deve deletar o produto do estoque referente ao número.

A opção (L)istar mostra uma lista com os produtos do estoque, exibindo seu nome, preço e quantidade disponível, respectivamente.

A opção (S)air salvará os dados dentro do vetor dinâmico no arquivo binário do estoque que só poderá ser modificado neste momento.

====================
ESTRUTURA DO PROJETO
====================

Biblioteca Vetor - biblioteca que comportará as funções que serão responsáveis por modificar o vetor.

	Função expandirVetor:
		Função que receberá o ponteiro do vetor atual, o tamanho do vetor atual e a quantidade de vezes que o vetor foi expandido.
		Criará um novo vetor de tamanho igual ao tamanho do vetor antigo mais 2 elevado a quantidade de vezes que o vetor foi exapndido.
		
	Função formatarNome:
		Função que receberá o ponteiro de uma string e transformará a primeira letra da string em maiúscula e o restante minúscula.



Biblioteca Pedidos - biblioteca que comportará funções para tratar os pedidos.

	Função lerPedido:
		Função que receberá o nome do arquivo a ser lido, e criará um vetor dinâmico de tamanho igual a quantidade de produtos no pedido. 
		Retorna um ponteiro que aponta ao vetor dinâmico.

	Função gerarNota:
		Função que receberá o ponteiro do vetor do pedido, e ponteiro do vetor do estoque, 
		Irá debitar os produtos do estoque, calcular o preço de cada produto, e o preço total, considerando o desconto de 10% para compras acima de 1000 reais.

	Função checarEstoque:
		Função que receberá o ponteiro do vetor do pedido e o ponteiro do vetor do estoque, e que vai testar se todos os produtos no estoque são o bastante para fornecer o pedido.
		Caso sim, chamará a função gerarNota, caso contrário, exibirá que o pedido falhhou e quais produtos causaram a falha.



Biblioteca Menu - biblioteca que comportará as funções que serão usadas no menu.

	Função Pedir:
		Função que chamará a função lerPedido, e checarEstoque.
		
		Pedir
		-----
		Arquivo: mamute.txt
		Pedido falhou!
		Molho: Solicitado = 40kg / Em estoque = 30kg
		Massa: Solicitado = 30kg / Em estoque = 10kg
		
		

	Função Adicionar:
		Função que recebe o ponteiro do vetor do estoque e que pedirá o nome, preço e quantidade do produto. 
		Adicionará o produto ao vetor do estoque, caso não tenha espaço chama a função expandirVetor.
		Caso o produto já exista, o preço será atualizado e a quantidade será somada.
		
		Adicionar
		---------
		Produto: Massa
		Preço: 2.50
		Quantidade: 50



	Função Excluir:
		Função que recebe o ponteiro do vetor do estoque e que pede um número escolhido pelo usuário que é correspondente a um produto nesta posição que será deletado.
		
		Excluir
		-------
		1) Massa
		2) Queijo
		3) Molho
		Número do produto: 1
		Deseja excluir "Massa" (S/N)? s



	Função Listar:
		Função que recebe o ponteiro do vetor do estoque e lista todos os produtos, com seu nome, preço e quantidade.
		
		Listagem
		--------
		Massa - R$2.50 - 10kg
		Queijo - R$15.00 - 100kg
		Molho - R$8.20 - 30kg



	Função Sair:
		Função que recebe o ponteiro do vetor do estoque e sobrescreve o arquivo binário do estoque com os valores do vetor e após, fecha o programa.

	Função Menu:
		Função que exibirá o menu e chamará as funções da biblioteca Menu, dependendo da opção escolhida.
		
		Sistema de Controle
		===================
		(P)edir
		(A)dicionar
		(E)xcluir
		(L)istar
		(S)air
		===================
		Opção: [_]
