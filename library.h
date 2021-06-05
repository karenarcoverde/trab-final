#include <iostream>
#include <sqlite3.h>


using namespace std;

#ifndef LIBRARY_H
#define LIBRARY_H



class Library{

	public:
		void criaTabela();
		string abreSQL(string);
		void inserirLivro (string, string, string, string, string);

	private:
		sqlite3* library;
};
#endif
