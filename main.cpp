

#include "library.h"



int main (){

	Library livros;
	int opcao_menu;

	livros.criaTabela ();

	while (opcao_menu != 7){

		cout << "------------------- MENU BIBLIOTECA ----------------------" << endl;
		cout << "| 1. Inserir livro                                       |" << endl;
		cout << "| 2. Remover Livro                                       |" << endl;
		cout << "| 3. Mostrar livros                                      |" << endl;
		cout << "| 4. Procurar livro                                      |" << endl;
		cout << "| 5. Realizar emprestimo                                 |" << endl;
		cout << "| 6. Realizar devolucao                                  |" << endl;
		cout << "| 7. Sair                                                |" << endl;
		cout << "----------------------------------------------------------" << endl;

		cin >> opcao_menu;

		switch (opcao_menu)
		{
		case 1:
			livros.inserirLivro ("Sistemas Digitais principios e aplicacoes", "Ronald Tocci", "eletronica digital", "Disponivel", "-");
			break;
		/*
		case 2:
			break;

		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6;
			break;
		*/
		case 7:
			break;

		default:
			cout << "Operacao invalida, escolha uma operacao existente. " << endl;
		}
	}
	return 0;
}
