Trabalho Final da disciplina de Linguagens de Programação.
Nomes: Jose Guilherme Silva de Macedo e Karen dos Anjos Arcoverde.

Programa que gerencia uma Biblioteca de Engenharia Eletrônica e de Computação.

Programa testado e feito no Linux.

PRÉ-REQUISITOS:
Ter sqlite3. 

A versão utilizada neste programa foi:
3.11.0 2016-02-15

Para verificar a existência de sqlite3 no seu computador, digite:
sqlite3 --version

Caso não possua, digite:
sudo apt install sqlite3
sudo apt install sqlite3 libsqlite3-dev
sudo add-apt-repository ppa:linuxgndu/sqlitebrowser
sudo apt install sqlitebrowser

Para compilar o programa, digite no terminal:
make

Para executar o programa, digite no terminal:
./programa

Para limpar os objetos e o executável, digite no terminal:
make clean

Instruções sobre o Menu:
O usuário deverá escolher uma opção das citadas abaixo. Ele poderá escolher quantas vezes quiser as opções enquanto não for escolhida a opção 9 (Sair).

1. Inserir Livro -> Insere um livro de acordo com o título, autor e gênero escolhido pelo usuário.  
2. Remover Livro -> Remove um livro de acordo com o título escolhido pelo usuário.
3. Mostrar livros -> Mostra todos os livros no banco de dados e com suas informações (título, autor, gênero, status e email).
4. Pesquisar livro por título-> Mostra todos os livros de acordo com o título escolhido pelo usuário.
5. Realizar emprestimo -> O usuário deve escolher o título do livro que deseja fazer o empréstimo.
6. Realizar devolucao -> O usuário deve escolher o título do livro que deseja fazer a devolução.
7. Pesquisar livro por genero-> Mostra todos os livros de acordo com o genero escolhido pelo usuário.
8. Pesquisar livro por e-mail-> Mostra todos os livros de acordo com o e-mail escolhido pelo usuário.
9. Sair -> O programa finaliza.
