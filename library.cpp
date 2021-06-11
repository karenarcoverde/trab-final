/***************************************************************************/
/*************************** library.cpp  *********************************/
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

void Library::mostraLivros (){
	const unsigned char* coluna1;
	const unsigned char* coluna2;
	const unsigned char* coluna3;
	const unsigned char* coluna4;
	const unsigned char* coluna5;
	
	string query = "";

	query = abreSQL("./mostra_tabela.sql");
	sqlite3_open ("livros.db", &library);

	sqlite3_prepare_v2 (library, query.c_str(), -1, &stmt, 0);

	while (sqlite3_step (stmt) != SQLITE_DONE){
		coluna1 = sqlite3_column_text (stmt, 0);
		coluna2 = sqlite3_column_text (stmt, 1);
		coluna3 = sqlite3_column_text (stmt, 2);
		coluna4 = sqlite3_column_text (stmt, 3);
		coluna5 = sqlite3_column_text (stmt, 4);

		cout << "\tTITULO: " << coluna1 << endl;
		cout << "\tAUTOR: " << coluna2 << endl;
		cout << "\tGENERO: " << coluna3 << endl;
		cout << "\tSTATUS: " << coluna4 << endl;
		cout << "\tEMAIL: " << coluna5 << endl;
		cout << "\n" << endl;
	}
	sqlite3_close(library);
}


//Callback para imprimir retorno das queries
static int callback (void *dados, int argc, char** argv, char** colunas){
	//fprintf(stderr, "%s: ", (const char*)dados);

	for (int idx = 0; idx < argc; idx++){
		printf("%s = %s\n", colunas[idx], argv[idx]  ? argv[idx] : "NULL");
	}
	printf("\n");

	return 0;
}



bool Library::pesquisaNomeLivro (string tituloLivro, bool imprimir = true){

	int info_sql = 0;
	char *erro;
	bool livro_existe = false;
	string query = "";

	//Abre arquivo SQL correponde a query de busca pelo nome e substitui a string referente ao titulo
	query = abreSQL("./busca_por_nome.sql");
	query.replace (query.find ("tituloLivro"), string ("tituloLivro").length(), tituloLivro);
	
	//abre o banco de dados
	sqlite3_open ("livros.db", &library);
	sqlite3_prepare_v2 (library, query.c_str(), -1, &stmt, 0);

	//checa de livro está no banco de dados
	if (sqlite3_step(stmt) != SQLITE_DONE){
		livro_existe = true;
	}
	while (sqlite3_step (stmt) != SQLITE_DONE);
	//imprime usando o callback definido acima
	if (imprimir)
		info_sql = sqlite3_exec(library, query.c_str(), callback, NULL, &erro);


	//Checagem de erros
	if (erro != NULL)
		cout << erro << endl;

	if (info_sql != SQLITE_OK){
		cerr << "Erro ao acessar tabela" << endl;
		sqlite3_free (erro);
	}
	else{
		if (imprimir)
			cout << "Pesquisa realizada com sucesso" << endl;
	}
	
	sqlite3_close(library);
	return livro_existe;
}

void Library::pesquisaNomeLivroLike (string tituloLivro){

	int info_sql = 0;
	char *erro;
	string query = "";

	//Abre arquivo SQL correponde a query de busca pelo nome e substitui a string referente ao titulo
	query = abreSQL("./busca_por_nome_like.sql");
	query.replace (query.find ("tituloLivro"), string ("tituloLivro").length(), "%" + tituloLivro + "%");
	
	//abre o banco de dados
	sqlite3_open ("livros.db", &library);
	sqlite3_prepare_v2 (library, query.c_str(), -1, &stmt, 0);

	//imprime usando o callback definido acima
	info_sql = sqlite3_exec(library, query.c_str(), callback, NULL, &erro);

	//Checagem de erros
	if (erro != NULL)
		cout << erro << endl;

	if (info_sql != SQLITE_OK){
		cerr << "Erro ao acessar tabela" << endl;
		sqlite3_free (erro);
	}
	else{
		cout << "Pesquisa realizada com sucesso" << endl;
	}
		
	sqlite3_close(library);
}
void Library::realizarEmprestimo(string tituloLivro, string email){

	string query = "";
	bool livroExiste = pesquisaNomeLivro(tituloLivro, false);

	if(livroExiste){

		const unsigned char* coluna4;
		query = abreSQL("./busca_status.sql");
		query.replace (query.find ("tituloLivro"), string ("tituloLivro").length(), tituloLivro );
		sqlite3_open ("livros.db", &library);

		sqlite3_prepare_v2 (library, query.c_str(), -1, &stmt, 0);
		
		sqlite3_step (stmt);
		coluna4 = sqlite3_column_text (stmt, 0);
		
		if ( strcmp((const char*)coluna4, "Disponivel") == 0 ){
			sqlite3_step (stmt);
			sqlite3_close(library);
			updateEmail(tituloLivro, email, "Indisponivel");
			cout << "Empréstimo realizado com sucesso" << endl;
		}
		else {
			sqlite3_step (stmt);
			sqlite3_close(library);
			cout << "Livro já foi emprestado. Tente novamente daqui a algum tempo" << endl;
	
		}
	}
	else{
		cout << "A biblioteca não possui esse livro, tente outro titulo" << endl;
	}

}
void Library::realizarDevolucao(string tituloLivro){

	string query = "";
	cout << endl;
	bool livroExiste = pesquisaNomeLivro(tituloLivro, false);
	if(livroExiste){

		const unsigned char* coluna4;
		query = abreSQL("./busca_status.sql");
		query.replace (query.find ("tituloLivro"), string ("tituloLivro").length(), tituloLivro );
		sqlite3_open ("livros.db", &library);

		sqlite3_prepare_v2 (library, query.c_str(), -1, &stmt, 0);
		
		sqlite3_step (stmt);
		coluna4 = sqlite3_column_text (stmt, 0);
		
		if ( strcmp((const char*)coluna4, "Indisponivel") == 0 ){
			sqlite3_step (stmt);
			sqlite3_close(library);
			updateEmail(tituloLivro, "-", "Disponivel");
			cout << "Devolucao realizada com sucesso" << endl;
		}
		else 
		{
			sqlite3_step (stmt);
			sqlite3_close(library);
			cout << "Livro não está emprestado. Verifique o titulo do livro e tente novamente" << endl;
	
		}
	}
	else{
		cout << "A biblioteca não possui esse livro, tente outro titulo" << endl;
	}
}


void Library::updateEmail(string tituloLivro, string email, string status){
	int info_sql = 0;
	char *erro;
	string query = "";


	query = abreSQL("./update_email.sql");
	query.replace (query.find ("tituloLivro"), string ("tituloLivro").length(), tituloLivro );
	query.replace (query.find ("email"), string ("email").length(), email );
	query.replace (query.find ("status"), string ("status").length(), status );
	sqlite3_open ("livros.db", &library);

	sqlite3_prepare_v2 (library, query.c_str(), -1, &stmt, 0);
	info_sql = sqlite3_exec(library, query.c_str(), NULL, 0, &erro);

	//Checagem de erros
	if (erro != NULL)
		cout << erro << endl;

	if (info_sql != SQLITE_OK){
		cerr << "Erro ao acessar tabela" << endl;
		sqlite3_free (erro);
	}
		
	sqlite3_close(library);
}

void Library::pesquisaEmail (string email){

	int info_sql = 0;
	char *erro;
	string query = "";

	//Abre arquivo SQL correponde a query de busca pelo nome e substitui a string referente ao titulo
	query = abreSQL("./busca_por_email.sql");
	query.replace (query.find ("email"), string ("email").length(), email);
	
	//abre o banco de dados
	sqlite3_open ("livros.db", &library);
	sqlite3_prepare_v2 (library, query.c_str(), -1, &stmt, 0);

	//imprime usando o callback definido acima
	info_sql = sqlite3_exec(library, query.c_str(), callback, NULL, &erro);

	//Checagem de erros
	if (erro != NULL)
		cout << erro << endl;

	if (info_sql != SQLITE_OK){
		cerr << "Erro ao acessar tabela" << endl;
		sqlite3_free (erro);
	}
	else{
		cout << "Pesquisa realizada com sucesso" << endl;
	}
		
	sqlite3_close(library);

}
void Library::pesquisaGenero (string genero){

	int info_sql = 0;
	char *erro;
	string query = "";

	//Abre arquivo SQL correponde a query de busca pelo nome e substitui a string referente ao titulo
	query = abreSQL("./busca_por_genero.sql");
	query.replace (query.find ("genero"), string ("genero").length(), genero);
	
	//abre o banco de dados
	sqlite3_open ("livros.db", &library);
	sqlite3_prepare_v2 (library, query.c_str(), -1, &stmt, 0);

	//imprime usando o callback definido acima
	info_sql = sqlite3_exec(library, query.c_str(), callback, NULL, &erro);

	//Checagem de erros
	if (erro != NULL)
		cout << erro << endl;

	if (info_sql != SQLITE_OK){
		cerr << "Erro ao acessar tabela" << endl;
		sqlite3_free (erro);
	}
	else{
		cout << "Pesquisa realizada com sucesso" << endl;
	}
		
	sqlite3_close(library);

}
