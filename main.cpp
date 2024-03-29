#include <iostream>
#include <conio.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "funcionario.cpp"
#include "hospede.cpp"
#include "suite.cpp"
#include "produto.cpp"
#include "hospedagem.cpp"
#include "venda.cpp"
#include <mysql.h>

using namespace std;

MYSQL  *servidor;
bool loginCHK = false;
string usuarioAtivoID, nomeUsuarioAtivo;

void conectar() {

    servidor= mysql_init(0);

    if(servidor==NULL) {
        cout<< "Verificando Banco de Dados...\n";
        getchar();
        exit(1);
    } else {
        if ( mysql_real_connect(servidor, "localhost", "root", "", NULL, 0, NULL, 0) ) {
            cout<<"\nBanco de dados conectado com sucesso!\n";
            mysql_autocommit ( servidor, 1 ) ;
        } else {
            cout<<"\nFalha ao conectar ao banco de dados\n";
            cout<<"Erro: BD01 "<< mysql_errno(servidor) << ", Mensagem: " << mysql_error(servidor)<<endl;
            getchar();
            mysql_close(servidor);
            exit(1);
        }
    }
}

void verificarEstruturaBD() {

    cout<<"\nVerificando Banco de Dados...\n";
    mysql_query(servidor, "CREATE DATABASE IF NOT EXISTS hoteldb");
    if(mysql_errno(servidor)==0) {
        cout<< "Banco de Dados criado com sucesso\n\n" ;
    } else {
        cout<<"\nErro na Cria��o do Bando de Dados: hotelbd "<< mysql_errno(servidor) << ", Mensagem: " << mysql_error(servidor)<<endl;
        exit(1);
    }
    mysql_select_db(servidor,"hoteldb");

    cout<<"\nVerificando estrutura das tabelas...\n";

    //Criando estrutura da tabela H�SPEDE
    mysql_query(servidor, "CREATE TABLE IF NOT EXISTS hospede (id int PRIMARY KEY AUTO_INCREMENT, nome varchar(120) NOT NULL, cpf varchar(14) UNIQUE NOT NULL , celular varchar(11), telefone varchar(11), uf varchar(2), data_nascimento date, cidade varchar (50), nacionalidade varchar(50))");
    if (mysql_errno(servidor)==0) {
        cout<< "Tabela HOSPEDE Criada com Sucesso!\n";
    } else {
        cout<<"\nErro na Cria��o da tabela no BD "<< mysql_errno(servidor) << ", Mensagem: " << mysql_error(servidor)<<endl;
        exit(1);
    }

    //Criando a estrutura da tabela da suite
    mysql_query(servidor, "CREATE TABLE IF NOT EXISTS suite (id int PRIMARY KEY AUTO_INCREMENT, numero SMALLINT UNIQUE NOT NULL, ramal VARCHAR(20), vagas SMALLINT(2)  , ocupacao varchar(15) DEFAULT ('disponivel'), preco DECIMAL(6,2))");
    if (mysql_errno(servidor)==0) {
        cout<< "Tabela SUITE Criada com Sucesso!\n";
    } else {
        cout<<"\nErro na Cria��o da tabela no BD "<< mysql_errno(servidor) << ", Mensagem: " << mysql_error(servidor)<<endl;
        exit(1);
    }

    //criando a estrutura da tabela de funcion�rio
    mysql_query(servidor, "CREATE TABLE IF NOT EXISTS funcionario (id int PRIMARY KEY AUTO_INCREMENT, nome varchar(120) NOT NULL, cpf varchar(14) UNIQUE NOT NULL , celular varchar(11), telefone varchar(11)  , uf varchar(2), data_nascimento date, cidade varchar (50), nacionalidade varchar(50), salario DECIMAL(6,2), atributo varchar(10), senha varchar(6))");
    if (mysql_errno(servidor)==0) {
        cout<< "Tabela FUNCIONARIO Criada com Sucesso!\n";
        mysql_query(servidor, "INSERT INTO funcionario (nome, cpf, senha) VALUES ('admin', '00000000000' ,'admin');");
    } else {
        cout<<"\nErro na Cria��o da tabela no BD "<< mysql_errno(servidor) << ", Mensagem: " << mysql_error(servidor)<<endl;
        exit(1);
    }

    //Criando a estrutura da tabela de produtos e servicos
    mysql_query(servidor, "CREATE TABLE IF NOT EXISTS produtos (id int PRIMARY KEY AUTO_INCREMENT, descricao VARCHAR(40), preco DECIMAL(6,2))");
    if (mysql_errno(servidor)==0) {
        cout<< "Tabela PRODUTO Criada com Sucesso!\n";
    } else {
        cout<<"\nErro na Cria��o da tabela no BD "<< mysql_errno(servidor) << ", Mensagem: " << mysql_error(servidor)<<endl;
        exit(1);
    }

    //criando a estrutura da tabela de hospedagem
    mysql_query(servidor, "CREATE TABLE IF NOT EXISTS hospedagem (id int PRIMARY KEY AUTO_INCREMENT, id_hospede int, id_suite int, data_entrada date, data_saida date, conta_final DECIMAL(6,2), forma_pagamento varchar(10))");
    mysql_query(servidor, "ALTER TABLE hospedagem ADD FOREIGN KEY (id_hospede) REFERENCES hospede(id);");
    mysql_query(servidor, "ALTER TABLE hospedagem ADD FOREIGN KEY (id_suite) REFERENCES suite(id);");

    if (mysql_errno(servidor)==0) {
        cout<< "Tabela HOSPEDAGEM Criada com Sucesso!\n";
    } else {
        cout<<"\nErro na Cria��o da tabela no BD "<< mysql_errno(servidor) << ", Mensagem: " << mysql_error(servidor)<<endl;
        exit(1);
    }

    //criando a estrutura da tabela de vendas
    mysql_query(servidor, "CREATE TABLE IF NOT EXISTS vendas (id int PRIMARY KEY AUTO_INCREMENT, id_hospedagem int, id_produto int, data_venda date, pagamento varchar(20), valor DECIMAL(6,2))");
    mysql_query(servidor, "ALTER TABLE vendas ADD FOREIGN KEY (id_produto) REFERENCES produto(id);");
    mysql_query(servidor, "ALTER TABLE vendas ADD FOREIGN KEY (id_hospedagem) REFERENCES hospedagem(id);");
    if (mysql_errno(servidor)==0) {
        cout<< "Tabela SERVI�O Criada com Sucesso!\n";
    } else {
        cout<<"\nErro na Cria��o da tabela no BD "<< mysql_errno(servidor) << ", Mensagem: " << mysql_error(servidor)<<endl;
        exit(1);
    }


}

void gotoxy(int coluna, int linha) {
    COORD point;
    point.X = coluna;
    point.Y = linha;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}

void textcolor(int color) {
// 0 1 2 3 4 5 6 7 8 ...
//typedef enum{BLACK,BLUE,GREEN,CYAN,RED,MAGENTA,BROWN,LIGHTGRAY,DARKGRAY,
//LIGHTBLUE,LIGHTGREEN,LIGHTCYAN,LIGHTRED,LIGHTMAGENTA,YELLOW,WHITE} COLORS;
// incluir a biblioteca windows.h
// este m�todo geralmente se encontra na biblioteca conio.h
// caso n�o esteja na biblioteca, use este metodo
    int __BACKGROUND = 0;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color + (__BACKGROUND << 4));
}

void desenharRetangulo (int base, int altura) {
    //Desenhar um ret�ngulo
    printf("%c",201);
    for (int i = 2; i<base; i++) {
        printf("%c",205);
    }
    printf("%c\n",187);

    for (int j = 2; j < altura; j++) {

        printf("%c",186);
        for (int i = 2; i<base; i++) {
            printf("%c",32);
        }
        printf("%c\n",186);

    }

    printf("%c",200);
    for (int i = 2; i<base; i++) {
        printf("%c",205);
    }
    printf("%c\n",188);
}

void desenharRetangulo2 (int base, int altura, int x, int y) {
    //Desenhar um ret�ngulo
    gotoxy(x, y++);
    printf("%c",201);
    for (int i = 2; i<base; i++) {
        printf("%c",205);
    }
    printf("%c\n",187);


    for (int j = 2; j < altura; j++) {
        gotoxy(x, y++);
        printf("%c",186);
        for (int i = 2; i<base; i++) {
            printf("%c",32);
        }
        printf("%c\n",186);

    }

    gotoxy(x, y++);
    printf("%c",200);
    for (int i = 2; i<base; i++) {
        printf("%c",205);
    }
    printf("%c\n",188);
}

void margemTela() {
    textcolor(5);
    system("CLS");
    desenharRetangulo(119,29);
}

void carregar () {
    textcolor(4);
    desenharRetangulo2(35,3,40,13);
    gotoxy(41,14);
    textcolor(1);
    for (int i = 0; i<33; i++) {
        Sleep(50);
        printf("%c",219);
    }
}

void telaLogin() {
    string login, senha;
    margemTela();
    textcolor(3);
    desenharRetangulo2(50,15,33,7);
    textcolor(2);
    gotoxy(40, 9);
    printf("SISTEMA DE GERENCIAMENTO HOTEL STEP");
    gotoxy(40, 12);
    printf("LOGIN:");
    gotoxy(40, 14);
    printf("SENHA:");
    gotoxy(40, 19);
    printf("Pressione ENTER para continuar");

    //Login
    bool logincheck;
    funcionario f;
    do {
        textcolor(1);
        gotoxy(47, 12);
        cin >> login;
        gotoxy(47, 14);
        cin >> senha;
        logincheck = f.fazerLogin(servidor, login, senha);
        gotoxy(47, 16);
        textcolor(2);
        printf("       Aguarde           ");
        gotoxy(47, 17);
        printf("                         ");
        gotoxy(47, 17);
        printf("        ");
        for (int i = 0; i<5; i++) {
            Sleep(300);
            cout <<".";
        }

        if( !logincheck) {
            textcolor(4);
            gotoxy(47, 12);
            printf("                        ");
            gotoxy(47, 14);
            printf("                        ");
            gotoxy(47, 16);
            printf("LOGIN OU SENHA INCORRETOS");
            gotoxy(47, 17);
            printf("    TENTE NOVAMENTE!");
        } else {
            gotoxy(47, 16);
            printf("  LOGIN E SENHA CORRETOS ");
            gotoxy(47, 17);
            carregar();
            loginCHK = true;
            usuarioAtivoID = f.salvarIDUsuario(servidor, login, senha);
            nomeUsuarioAtivo = login;
        }
    } while (!logincheck);
    gotoxy(0,29);

}

int main() {
    conectar();
    verificarEstruturaBD();
    setlocale(LC_ALL, "pt_BR_utf8");
    do {//Loop de tela de Login
        if(!loginCHK) {
            telaLogin();
            Sleep(500);
        }
        int opMenu;
        bool erro  = false;
        do { // Loop de menu principal
            system("CLS");
            margemTela();
            gotoxy(4,0);
            textcolor(3);
            cout << "Usuario:  " << nomeUsuarioAtivo;
            int x = 40,y = 3;
            gotoxy(x,y++);
            textcolor(6);
            cout << "- - - -    MENU PRINCIPAL    - - - -";
            y++;
            y++;
            gotoxy(x,y++);
            y++;
            textcolor(2);
            cout << "    1 - HOSPEDES";
            gotoxy(x,y++);
            y++;
            cout << "    2 - SUITES";
            gotoxy(x,y++);
            y++;
            cout << "    3 - FUNCIONARIOS";
            gotoxy(x,y++);
            y++;
            cout << "    4 - SERVICOS E PRODUTOS";
            gotoxy(x,y++);
            y++;
            cout << "    5 - HOSPEDAGEM";
            gotoxy(x,y++);
            y++;
            cout << "    6 - VENDA";
            gotoxy(x,y++);
            y++;
            cout << "    7 - LOGOFF";
            gotoxy(x,y++);
            y++;
            cout << "    8 - FECHAR PROGRAMA";
            y++;
            gotoxy(x,++y);
            textcolor(1);
            cout << "    Digite a opcao desejada: ";
            if (erro) {
                gotoxy(40,26);
                textcolor(14);
                cout << "Opcao Invalida. Tente Novamente!";
            }
            erro = false;
            textcolor(1);
            gotoxy(x+29,y);
            cin >>opMenu;

            switch (opMenu) {
            case 1: { // H�spedes
                gotoxy(40,26);
                cout << "                               ";
                carregar();
                gotoxy(45,26);
                textcolor(14);

                int opMenuHospede;
                bool erroHospede  = false;

                do {
                    system("CLS");
                    margemTela();
                    gotoxy(4,0);
                    textcolor(3);
                    cout << "Usuario:  " << nomeUsuarioAtivo;
                    int x = 40,y = 3;
                    gotoxy(x,y++);
                    textcolor(15);
                    cout << "- - - -    MENU HOSPEDE    - - - -";
                    y++;
                    y++;
                    gotoxy(x,y++);
                    y++;
                    textcolor(14);
                    cout << "    1 - CADASTRAR HOSPEDE";
                    gotoxy(x,y++);
                    y++;
                    cout << "    2 - LOCALIZAR HOSPEDE POR NOME";
                    gotoxy(x,y++);
                    y++;
                    cout << "    3 - LOCALIZAR HOSPEDE POR CPF";
                    gotoxy(x,y++);
                    y++;
                    cout << "    4 - EDITAR INFORMACOES DE HOSPEDE";
                    gotoxy(x,y++);
                    y++;
                    cout << "    5 - DELETAR HOSPEDE";
                    gotoxy(x,y++);
                    y++;
                    cout << "    6 - IMPRIMIR QUANTIDADE DE HOSPEDES CADASTRADOS";
                    gotoxy(x,y++);
                    y++;
                    cout << "    7 - LISTAR HOSPEDES POR UF";
                    gotoxy(x,y++);
                    y++;
                    cout << "    8 - VOLTAR AO MENU PRINCIPAL";
                    y++;
                    gotoxy(x,++y);
                    textcolor(1);
                    cout << "    Digite a opcao desejada: ";
                    if (erroHospede) {
                        gotoxy(40,26);
                        textcolor(14);
                        cout << "Opcao Invalida. Tente Novamente!";
                    }
                    erroHospede = false;
                    textcolor(1);
                    gotoxy(x+29,y);
                    cin >>opMenuHospede;

                    switch (opMenuHospede) {
                    case 1: { //Cadastrar H�spede
                        hospede h;
                        h.cadastrarHospede(servidor);
                        opMenuHospede = 0;
                        break;
                    }
                    case 2: { //LOCALIZAR HOSPEDE POR NOME
                        hospede h;
                        h.localizarPorNome(servidor);
                        opMenuHospede = 0;
                        break;
                    }
                    case 3: { //LOCALIZAR HOSPEDE POR CPF
                        hospede h;
                        h.localizarPorCPF(servidor);
                        opMenuHospede = 0;
                        break;
                    }
                    case 4: { //EDITAR INFORMACOES DE HOSPEDE
                        hospede h;
                        h.editarHospede(servidor);
                        opMenuHospede = 0;
                        break;
                    }
                    case 5: { //DELETAR hospede
                        hospede h;
                        h.excluirHospede(servidor);
                        opMenuHospede = 0;
                        break;
                    }
                    case 6: {
                        hospede h;
                        h.contarhospedes(servidor);
                        getchar();
                        opMenuHospede = 0;
                        break;
                    }
                    case 7: { //Listar H�spedes por UF
                        hospede h;
                        h.listarporUF(servidor);
                        getchar();
                        opMenuHospede = 0;
                        break;
                    }
                    case 8: {
                        gotoxy(45,26);
                        textcolor(14);
                        cout << "Voltando ao menu principal";
                        carregar();
                        gotoxy(0,29);
                        break;
                    }
                    default: {
                        gotoxy(40,26);
                        textcolor(14);
                        cout << "Opcao Invalida. Tente Novamente!";
                        erro = true;
                        break;
                        break;
                    }
                    }

                } while (opMenuHospede < 1 || opMenuHospede >8);

                opMenu = 0; //Voltar ao loop do menu principal
                break;
            }
            case 2: { //SUITES
                gotoxy(40,26);
                cout << "                               ";
                carregar();
                gotoxy(45,26);
                textcolor(14);

                int opMenuSuite;
                bool erro  = false;

                do {
                    system("CLS");
                    margemTela();
                    gotoxy(4,0);
                    textcolor(3);
                    cout << "Usuario:  " << nomeUsuarioAtivo;
                    int x = 40,y = 3;
                    gotoxy(x,y++);
                    textcolor(15);
                    cout << "- - - -    MENU SUITES    - - - -";
                    y++;
                    y++;
                    gotoxy(x,y++);
                    y++;
                    textcolor(14);
                    cout << "    1 - CADASTRAR SUITE";
                    gotoxy(x,y++);
                    y++;
                    cout << "    2 - LOCALIZAR SUITE POR NUMERO";
                    gotoxy(x,y++);
                    y++;
                    cout << "    3 - LISTAR SUITES POR STATUS";
                    gotoxy(x,y++);
                    y++;
                    cout << "    4 - EDITAR INFORMACOES DE SUITE";
                    gotoxy(x,y++);
                    y++;
                    cout << "    5 - DELETAR SUITE";
                    gotoxy(x,y++);
                    y++;
                    cout << "    6 - VOLTAR AO MENU PRINCIPAL";
                    y++;
                    gotoxy(x,++y);
                    textcolor(1);
                    cout << "    Digite a opcao desejada: ";
                    if (erro) {
                        gotoxy(40,26);
                        textcolor(14);
                        cout << "Opcao Invalida. Tente Novamente!";
                    }
                    erro = false;
                    textcolor(1);
                    gotoxy(x+29,y);
                    cin >>opMenuSuite;

                    switch (opMenuSuite) {
                    case 1: { //Cadastrar Suite
                        suite s;
                        s.cadastrarSuite(servidor);
                        opMenuSuite = 0;
                        break;
                    }
                    case 2: { //LOCALIZAR Suite por numero
                        suite s;
                        s.localizarPorNumero(servidor);
                        opMenuSuite = 0;
                        break;
                    }
                    case 3: { //Listar suites por status
                        suite s;
                        s.listarPorStatus(servidor);
                        opMenuSuite = 0;
                        break;
                    }
                    case 4: { //EDITAR INFORMACOES DE Suite
                        suite s;
                        s.editarSuite(servidor);
                        opMenuSuite = 0;
                        break;
                    }
                    case 5: { //DELETAR hospede
                        suite s;
                        s.excluirSuite(servidor);
                        opMenuSuite = 0;
                        break;
                    }
                    case 6: {
                        gotoxy(45,26);
                        textcolor(14);
                        cout << "Voltando ao menu principal";
                        carregar();
                        gotoxy(0,29);
                        break;
                    }
                    default: {
                        gotoxy(40,26);
                        textcolor(14);
                        cout << "Opcao Invalida. Tente Novamente!";
                        erro = true;
                        ;
                        break;
                    }
                    }

                } while (opMenuSuite < 1 || opMenuSuite >6);
                opMenu = 0;
                break;
            }
            case 3: { //FUNCIONARIOS
                gotoxy(40,26);
                cout << "                               ";
                carregar();
                gotoxy(45,26);
                textcolor(14);

                int opMenuFuncionario;
                bool erro  = false;

                do {
                    system("CLS");
                    margemTela();
                    gotoxy(4,0);
                    textcolor(3);
                    cout << "Usuario:  " << nomeUsuarioAtivo;
                    int x = 40,y = 3;
                    gotoxy(x,y++);
                    textcolor(15);
                    cout << "- - - -    MENU FUNCIONARIOSS    - - - -";
                    y++;
                    y++;
                    gotoxy(x,y++);
                    y++;
                    textcolor(14);
                    cout << "    1 - CADASTRAR FUNCIONARIOS";
                    gotoxy(x,y++);
                    y++;
                    cout << "    2 - LOCALIZAR FUNCIONARIOS POR NOME";
                    gotoxy(x,y++);
                    y++;
                    cout << "    3 - EDITAR INFORMACOES DE FUNCIONARIO";
                    gotoxy(x,y++);
                    y++;
                    cout << "    4 - DELETAR FUNCIONARIO";
                    gotoxy(x,y++);
                    y++;
                    cout << "    5 - VOLTAR AO MENU PRINCIPAL";
                    y++;
                    gotoxy(x,++y);
                    textcolor(1);
                    cout << "    Digite a opcao desejada: ";
                    if (erro) {
                        gotoxy(40,26);
                        textcolor(14);
                        cout << "Opcao Invalida. Tente Novamente!";
                    }
                    erro = false;
                    textcolor(1);
                    gotoxy(x+29,y);
                    cin >>opMenuFuncionario;

                    switch (opMenuFuncionario) {
                    case 1: { //Cadastrar FUNCIONARIO
                        funcionario f;
                        f.cadastrarFuncionario(servidor);
                        opMenuFuncionario = 0;
                        break;
                    }
                    case 2: { //LOCALIZAR FUNCIONARIO por NOME
                        funcionario f;
                        f.localizarPorNome(servidor);
                        opMenuFuncionario = 0;
                        break;
                    }
                    case 3: { //EDITAR INFORMACOES DE Funcionario
                        funcionario f;
                        f.editarFuncionario(servidor);
                        opMenuFuncionario = 0;
                        break;
                    }
                    case 4: { //DELETAR funcionario
                        funcionario f;
                        f.excluirFuncionario(servidor);
                        opMenuFuncionario = 0;
                        break;
                    }
                    case 5: {
                        gotoxy(45,26);
                        textcolor(14);
                        cout << "Voltando ao menu principal";
                        carregar();
                        gotoxy(0,29);
                        break;
                    }
                    default: {
                        gotoxy(40,26);
                        textcolor(14);
                        cout << "Opcao Invalida. Tente Novamente!";
                        erro = true;
                        break;
                        break;
                    }
                    }

                } while (opMenuFuncionario < 1 || opMenuFuncionario >5);
                opMenu = 0;
                break;

            }
            case 4: { //SERVI�OS e produtos
                gotoxy(40,26);
                cout << "                               ";
                carregar();
                gotoxy(45,26);
                textcolor(14);

                int opMenuProduto;
                bool erro  = false;

                do {
                    system("CLS");
                    margemTela();
                    gotoxy(4,0);
                    textcolor(3);
                    cout << "Usuario:  " << nomeUsuarioAtivo;
                    int x = 40,y = 3;
                    gotoxy(x,y++);
                    textcolor(15);
                    cout << "- - - -    MENU PRODUTOS    - - - -";
                    y++;
                    y++;
                    gotoxy(x,y++);
                    y++;
                    textcolor(14);
                    cout << "    1 - CADASTRAR PRODUTO";
                    gotoxy(x,y++);
                    y++;
                    cout << "    2 - LOCALIZAR PRODUTO POR NUMERO";
                    gotoxy(x,y++);
                    y++;
                    cout << "    3 - LISTAR PRODUTOS POR STATUS";
                    gotoxy(x,y++);
                    y++;
                    cout << "    4 - EDITAR INFORMACOES DE PRODUTO";
                    gotoxy(x,y++);
                    y++;
                    cout << "    5 - DELETAR PRODUTO";
                    gotoxy(x,y++);
                    y++;
                    cout << "    6 - VOLTAR AO MENU PRINCIPAL";
                    y++;
                    gotoxy(x,++y);
                    textcolor(1);
                    cout << "    Digite a opcao desejada: ";
                    if (erro) {
                        gotoxy(40,26);
                        textcolor(14);
                        cout << "Opcao Invalida. Tente Novamente!";
                    }
                    erro = false;
                    textcolor(1);
                    gotoxy(x+29,y);
                    cin >>opMenuProduto;

                    switch (opMenuProduto) {
                    case 1: { //Cadastrar Produto
                        produto s;
                        s.cadastrarProduto(servidor);
                        opMenuProduto = 0;
                        break;
                    }
                    case 2: { //LOCALIZAR Produto
                        produto s;
                        s.localizarPorDescricao(servidor);
                        opMenuProduto = 0;
                        break;
                    }
                    case 3: { //Listar produtos
                        produto s;
                        s.listarPorDescricao(servidor);
                        opMenuProduto = 0;
                        break;
                    }
                    case 4: { //EDITAR INFORMACOES DE Produto
                        produto s;
                        s.editarProduto(servidor);
                        opMenuProduto = 0;
                        break;
                    }
                    case 5: { //DELETAR produto
                        produto s;
                        s.excluirProduto(servidor);
                        opMenuProduto = 0;
                        break;
                    }
                    case 6: {
                        gotoxy(45,26);
                        textcolor(14);
                        cout << "Voltando ao menu principal";
                        carregar();
                        gotoxy(0,29);
                        break;
                    }
                    default: {
                        gotoxy(40,26);
                        textcolor(14);
                        cout << "Opcao Invalida. Tente Novamente!";
                        erro = true;
                        ;
                        break;
                    }
                    }

                } while (opMenuProduto < 1 || opMenuProduto >6);
                opMenu = 0;
                break;

            }
            case 5: { //HOSPEDAGENS
                gotoxy(40,26);
                cout << "                               ";
                carregar();
                gotoxy(45,26);
                textcolor(14);

                int opMenuHospedagem;
                bool erroHospedagem  = false;

                do {
                    system("CLS");
                    margemTela();
                    gotoxy(4,0);
                    textcolor(3);
                    cout << "Usuario:  " << nomeUsuarioAtivo;
                    int x = 40,y = 3;
                    gotoxy(x,y++);
                    textcolor(15);
                    cout << "- - - -    MENU HOSPEDAGEM    - - - -";
                    y++;
                    y++;
                    gotoxy(x,y++);
                    y++;
                    textcolor(14);
                    cout << "    1 - CADASTRAR HOSPEDAGEM";
                    gotoxy(x,y++);
                    y++;
                    cout << "    2 - LOCALIZAR HOSPEDAGEM POR HOSPEDE";
                    gotoxy(x,y++);
                    y++;
                    y++;
                    cout << "    3 - ENCERRAR HOSPEDAGEM";
                    gotoxy(x,y++);
                    y++;
                    cout << "    4 - VOLTAR AO MENU PRINCIPAL";
                    y++;
                    gotoxy(x,++y);
                    textcolor(1);
                    cout << "    Digite a opcao desejada: ";
                    if (erroHospedagem) {
                        gotoxy(30,26);
                        textcolor(14);
                        cout << "Opcao Invalida ou nao ha suite disponivel. Tente Novamente!";
                    }
                    erroHospedagem = false;
                    textcolor(1);
                    gotoxy(x+29,y);
                    cin >>opMenuHospedagem;

                    switch (opMenuHospedagem) {
                    case 1: { //Cadastrar H�spede
                        hospedagem h;
                        suite s;
                        erroHospedagem = false;
                        carregar();
                        if (s.verificarDisponibilidade(servidor)) {
                            h.cadastrarHospedagem(servidor);

                        } else {
                            erroHospedagem = true;
                        }

                        opMenuHospedagem = 0;
                        break;
                    }
                    case 2: { //LOCALIZAR HOSPEDAGEM POR NOME DO HOSPEDE
                        hospedagem h;
                        h.localizarPorNome(servidor);
                        opMenuHospedagem = 0;
                        break;
                    }
                    case 3: { //Encerrar Hospedagem
                        hospedagem h;
                        h.encerrarHospedagem(servidor);
                        opMenuHospedagem = 0;
                        break;
                    }
                    case 4: {
                        gotoxy(45,26);
                        textcolor(14);
                        cout << "Voltando ao menu principal";
                        carregar();
                        gotoxy(0,29);
                        break;
                    }
                    default: {
                        gotoxy(40,26);
                        textcolor(14);
                        cout << "Opcao Invalida. Tente Novamente!";
                        erro = true;
                        break;
                        break;
                    }
                    }

                } while (opMenuHospedagem < 1 || opMenuHospedagem >8);

                opMenu = 0; //Voltar ao loop do menu principal
                break;

            }
            case 6: { // VENDAS
                gotoxy(40,26);
                cout << "                               ";
                carregar();
                gotoxy(45,26);
                textcolor(14);

                int opMenuVenda;
                bool erroVenda  = false;

                do {
                    system("CLS");
                    margemTela();
                    gotoxy(4,0);
                    textcolor(3);
                    cout << "Usuario:  " << nomeUsuarioAtivo;
                    int x = 40,y = 3;
                    gotoxy(x,y++);
                    textcolor(15);
                    cout << "- - - -    MENU VENDA    - - - -";
                    y++;
                    y++;
                    gotoxy(x,y++);
                    y++;
                    textcolor(14);
                    cout << "    1 - REGISTRAR VENDA";
                    gotoxy(x,y++);
                    y++;
                    cout << "    2 - CANCELAR VENDA";
                    gotoxy(x,y++);
                    y++;
                    cout << "    3 - VOLTAR AO MENU PRINCIPAL";
                    y++;
                    gotoxy(x,++y);
                    textcolor(1);
                    cout << "    Digite a opcao desejada: ";
                    if (erroVenda) {
                        gotoxy(30,26);
                        textcolor(14);
                        cout << "Opcao Invalida ou nao ha suite disponivel. Tente Novamente!";
                    }
                    erroVenda = false;
                    textcolor(1);
                    gotoxy(x+29,y);
                    cin >>opMenuVenda;

                    switch (opMenuVenda) {
                    case 1: { //Cadastrar H�spede
                        venda v;
                        suite s;
                        erroVenda = false;
                        carregar();
                        if (s.verificarDisponibilidade(servidor)) {
                            v.registrarVenda(servidor);

                        } else {
                            erroVenda = true;
                        }

                        opMenuVenda = 0;
                        break;
                    }
                    case 2: { //Encerrar Venda
                        venda v;
                        v.cancelarVenda(servidor);
                        opMenuVenda = 0;
                        break;
                    }
                    case 3: {
                        gotoxy(45,26);
                        textcolor(14);
                        cout << "Voltando ao menu principal";
                        carregar();
                        gotoxy(0,29);
                        break;
                    }
                    default: {
                        gotoxy(40,26);
                        textcolor(14);
                        cout << "Opcao Invalida. Tente Novamente!";
                        erro = true;
                        break;
                        break;
                    }
                    }

                } while (opMenuVenda < 1 || opMenuVenda >8);

                opMenu = 0; //Voltar ao loop do menu principal
                break;
            }
            case 7: {
                gotoxy(40,26);
                cout << "                               ";
                gotoxy(45,26);
                textcolor(14);
                cout << "Fazendo Logoff";
                carregar();
                loginCHK = false;
                break;
            }
            case 8: {
                gotoxy(40,26);
                cout << "                               ";
                gotoxy(45,26);
                textcolor(14);
                cout << "Saindo do programa";
                carregar();
                gotoxy(0,29);
                exit(1);
                break;
            }
            default: {
                gotoxy(40,26);
                textcolor(14);
                cout << "Opcao Invalida. Tente Novamente!";
                erro = true;
                break;
            }
            }
        } while (opMenu<1||opMenu>8);

    } while (!loginCHK);
    gotoxy(0,29);

    return 0;
}
