/***************************************************************************/
/*************************** Programa Principal ****************************/

#include "library.h"
#include <limits>

using namespace std;


int main (){

	Library livros;
	int opcao_menu;
	string tituloLivro;
	string autorLivro;
	string generoLivro;
	string email;
	bool livro_existe;

	livros.criaTabela ();

	opcao_menu = 0;
	while (opcao_menu != 9){

		cout << "------------------- MENU BIBLIOTECA ----------------------" << endl;
		cout << "| 1. Inserir livro                                       |" << endl;
		cout << "| 2. Remover Livro                                       |" << endl;
		cout << "| 3. Mostrar livros                                      |" << endl;
		cout << "| 4. Pesquisar livro por título                          |" << endl;
		cout << "| 5. Realizar emprestimo                                 |" << endl;
		cout << "| 6. Realizar devolucao                                  |" << endl;
		cout << "| 7. Pesquisar livro por genero                          |" << endl;
		cout << "| 8. Pesquisar livro por e-mail                          |" << endl;
		cout << "| 9. Sair                                                |" << endl;
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
			else
				cout << "\nEsse livro ja existe na biblioteca. Digite novamente.\n" << endl;
			break;

		case 2:

			cout << "\nTitulo: " << endl;
			cin.ignore();
			getline (cin, tituloLivro);
			/*verifica se o livro esta na biblioteca */
			livro_existe = livros.pesquisaNomeLivro (tituloLivro, false);

			if (livro_existe)
					livros.removerLivro (tituloLivro);
			else{
				cin.clear();
				cout << "\nLivro nao consta na biblioteca. Digite corretamente.\n" << endl;
			}
			break;

		case 3:
			livros.mostraLivros();
			break;

		case 4:
			cout << "\nTitulo: " << endl;
			cin.ignore();
			getline (cin, tituloLivro);
			
			if (tituloLivro == " ") cout << "Nome inválido!" << endl;
			else livros.pesquisaNomeLivroLike(tituloLivro);
			break;
		case 5:
			cout << "\nTitulo: " << endl;
			cin.clear();
			cin.ignore();
			getline (cin, tituloLivro);
			
			cout << "\nEmail: " << endl;
			cin.clear();
			getline (cin, email);
			
			livros.realizarEmprestimo(tituloLivro, email);

			break;
	
		case 6:
			cout << "\nTitulo: " << endl;
			cin.clear();
			cin.ignore();
			getline (cin, tituloLivro);
			livros.realizarDevolucao(tituloLivro);
			break;
		
		case 7:
			
			cout << "\nGenero: " << endl;
			cin.ignore();
			getline (cin, generoLivro);
			
			livros.pesquisaGenero(generoLivro);
			
			break;
		case 8:
			cout << "\nEmail: " << endl;
			cin.ignore();
			getline (cin, email);
			
			livros.pesquisaEmail(email);
		       	break;
		case 9:
			cout << "Programa encerrado!" << endl;
			break;

		default:
			while(cin.fail() || cin.bad()){
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			cout << "Operacao invalida, escolha uma operacao existente. " << endl;
			opcao_menu = 0;
		}
	}
	return 0;
}
