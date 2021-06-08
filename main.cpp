/***************************************************************************/
/*************************** Programa Principal ****************************/

#include "library.h"

using namespace std;


int main (){

	Library livros;
	int opcao_menu;
	string tituloLivro;
	string autorLivro;
	string generoLivro;
	bool livro_existe; 
		
	livros.criaTabela ();

	while (opcao_menu != 7){

		cout << "------------------- MENU BIBLIOTECA ----------------------" << endl;
		cout << "| 1. Inserir livro                                       |" << endl;
		cout << "| 2. Remover Livro                                       |" << endl;
		cout << "| 3. Mostrar livros                                      |" << endl;
		cout << "| 4. Pesquisar livro                                     |" << endl;
		cout << "| 5. Realizar emprestimo                                 |" << endl;
		cout << "| 6. Realizar devolucao                                  |" << endl;
		cout << "| 7. Sair                                                |" << endl;
		cout << "----------------------------------------------------------" << endl;

		cin >> opcao_menu;

		switch (opcao_menu)
		{
		case 1:
			cout << "\nTitulo: " << endl;
			cin.clear();
			cin.ignore();
			getline (cin, tituloLivro);

			/* verifica se ja existe esse nome do livro sem imprimir caso o livre esteja lá*/
			livro_existe = livros.pesquisaNomeLivro (tituloLivro, false);

			if (!livro_existe){

				cout << "\nAutor: " << endl;
				cin.clear();
				getline (cin, autorLivro);

				cout << "\nGenero: " << endl;
				cin.clear();
				getline (cin, generoLivro);

				livros.inserirLivro (tituloLivro, autorLivro, generoLivro, "Disponivel", "-");
			}
			break;

		case 2:
			/*verifica se o livro esta na biblioteca */
			livro_existe = livros.pesquisaNomeLivro (tituloLivro, false);

			if (livro_existe){
				cout << "\nTitulo: " << endl;
				cin.ignore();
				getline (cin, tituloLivro);

				livros.removerLivro (tituloLivro);
				break;

		case 3:
			livros.mostraLivros();
			break;

		/*
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
			cin.ignore();
		}
	}
	return 0;
}
