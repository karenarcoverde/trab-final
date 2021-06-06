/***************************************************************************/
/*************************** library.cpp  *********************************/

#include <iostream>
#include <sqlite3.h>
#include <fstream>
#include <string>

#include "library.h"


string Library::abreSQL (string ArquivoSQL){

	string query = "";
	string linha_arquivo = "";

	fstream arquivo;
	arquivo.open (ArquivoSQL.c_str(), fstream::in);

	if (arquivo.is_open()){
		while (getline(arquivo,linha_arquivo))
			query += linha_arquivo;

		arquivo.close();

	}
	else
		cout << "Erro ao abrir o arquivo." << endl;

	return query;
}

void Library::criaTabela (){

	char *erro;
	int info_sql = 0;

	string query = "";

	query = abreSQL ("./cria_tabela.sql");

	sqlite3_open("livros.db", &library);

	info_sql = sqlite3_exec(library, query.c_str(), NULL, 0, & erro);
	if (info_sql != SQLITE_OK){
		/*tabela ja foi criada */
		sqlite3_free(erro);
	}
	else
		cout << "\nTabela criada. \n" << endl;

	sqlite3_close(library);
}

void Library::inserirLivro (string tituloLivro, string autorLivro, string generoLivro, string statusLivro, string emailCliente){

	string query = "";
	char* erro;
	int info_sql = 0;

	query = abreSQL ("./insere_livro.sql");

	query.replace (query.find ("tituloLivro"), string ("tituloLivro").length(), tituloLivro);
	query.replace (query.find ("autorLivro"), string ("autorLivro").length(), autorLivro);
	query.replace (query.find ("generoLivro"), string ("generoLivro").length(), generoLivro);
	query.replace (query.find ("statusLivro"), string ("statusLivro").length (), statusLivro);
	query.replace (query.find ("emailCliente"), string ("emailCliente").length(), emailCliente);

	sqlite3_open("livros.db", &library);

	info_sql = sqlite3_exec (library, query.c_str(), NULL, 0, & erro);

	if (erro != NULL)
		cout << erro << endl;

	if (info_sql != SQLITE_OK){
		cout << "\nErro ao acessar a tabela.\n" << endl;
		sqlite3_free (erro);
	}
	else
		cout << "\nLivro inserido na Biblioteca!\n" << endl;

	sqlite3_close(library);
}


void Library::removerLivro (string tituloLivro){

		char *erro;
		string query = "";
		int info_sql = 0;

		query = abreSQL ("./remove_livro.sql");

		query.replace (query.find ("tituloLivro"), string ("tituloLivro").length(), tituloLivro);

		sqlite3_open("livros.db", &library);
		info_sql = sqlite3_exec (library, query.c_str(), NULL, 0, & erro);

		if (erro != NULL)
				cout << erro << endl;

		if (info_sql != SQLITE_OK){
				cout << "\nErro ao acessar tabela.\n" << endl;
			  sqlite3_free (erro);
		}

		else
				cout << "\nLivro removido da Biblioteca!\n" << endl;

		sqlite3_close(library);
}

/*

bool Library::pesquisaNomeLivro (string tituloLivro){

		bool livro_existe = false;
		query = "SELECT * FROM LIVROS;";
} */
