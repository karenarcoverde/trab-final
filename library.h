/***************************************************************************/
/*************************** library.h  ***********************************/

#include <iostream>
#include <sqlite3.h>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

#ifndef LIBRARY_H
#define LIBRARY_H

class Library{

	public:
		void criaTabela();
		string abreSQL(string);
		void inserirLivro (string, string, string, string, string);
		void removerLivro (string);
		void mostraLivros ();
		bool pesquisaNomeLivro (string, bool); //nome exato
		void pesquisaNomeLivroLike (string); //busca nome que contenha a string
		void realizarEmprestimo(string, string);
		void realizarDevolucao(string);

	private:
		sqlite3* library;
		sqlite3_stmt* stmt;
		void updateEmail (string, string, string);

};
#endif
