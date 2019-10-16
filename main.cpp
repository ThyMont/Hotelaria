#include <iostream>
#include <conio.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "funcionario.cpp"
#include <mysql.h>

using namespace std;

MYSQL  *servidor;
bool loginCHK;
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
        cout<<"\nErro na Criação do Bando de Dados: hotelbd "<< mysql_errno(servidor) << ", Mensagem: " << mysql_error(servidor)<<endl;
        exit(1);
    }
    mysql_select_db(servidor,"hoteldb");

    cout<<"\nVerificando estrutura das tabelas...\n";

    //Criando estrutura da tabela HÓSPEDE
    mysql_query(servidor, "CREATE TABLE IF NOT EXISTS hospede (id int PRIMARY KEY AUTO_INCREMENT, nome varchar(120) NOT NULL, cpf varchar(14) UNIQUE NOT NULL , celular varchar(11), telefone varchar(11), uf varchar(2), data_nascimento date, cidade varchar (50), nacionalidade varchar(50))");
    if (mysql_errno(servidor)==0) {
        cout<< "Tabela HOSPEDE Criada com Sucesso!\n";
    } else {
        cout<<"\nErro na Criação da tabela no BD "<< mysql_errno(servidor) << ", Mensagem: " << mysql_error(servidor)<<endl;
        exit(1);
    }

    //Criando a estrutura da tabela da suite
    mysql_query(servidor, "CREATE TABLE IF NOT EXISTS suite (id int PRIMARY KEY AUTO_INCREMENT, numero SMALLINT UNIQUE NOT NULL, vagas SMALLINT(2)  , status varchar(15) DEFAULT ('N'), preco DECIMAL(6,2))");
    if (mysql_errno(servidor)==0) {
        cout<< "Tabela SUITE Criada com Sucesso!\n";
    } else {
        cout<<"\nErro na Criação da tabela no BD "<< mysql_errno(servidor) << ", Mensagem: " << mysql_error(servidor)<<endl;
        exit(1);
    }

    //criando a estrutura da tabela de funcionário
    mysql_query(servidor, "CREATE TABLE IF NOT EXISTS funcionario (id int PRIMARY KEY AUTO_INCREMENT, nome varchar(120) NOT NULL, cpf varchar(14) UNIQUE NOT NULL , celular varchar(11), telefone varchar(11)  , uf varchar(2), data_nascimento date, cidade varchar (50), nacionalidade varchar(50), salario DECIMAL(6,2), atributo varchar(10), senha varchar(6))");
    if (mysql_errno(servidor)==0) {
        cout<< "Tabela FUNCIONARIO Criada com Sucesso!\n";
        mysql_query(servidor, "INSERT INTO funcionario (nome, cpf, senha) VALUES ('admin', '00000000000' ,'admin');");
    } else {
        cout<<"\nErro na Criação da tabela no BD "<< mysql_errno(servidor) << ", Mensagem: " << mysql_error(servidor)<<endl;
        exit(1);
    }

    //criando a estrutura da tabela de hospedagem
    mysql_query(servidor, "CREATE TABLE IF NOT EXISTS hospedagem (id int PRIMARY KEY AUTO_INCREMENT, id_hospede int, id_suite int, id_funcionario int, data_entrada date, data_saida date, status varchar(20), conta_final DECIMAL(6,2), forma_pagamento varchar(10), senha varchar(6))");
    mysql_query(servidor, "ALTER TABLE hospedagem ADD FOREIGN KEY (id_hospede) REFERENCES hospede(id);");
    mysql_query(servidor, "ALTER TABLE hospedagem ADD FOREIGN KEY (id_suite) REFERENCES suite(id);");
    mysql_query(servidor, "ALTER TABLE hospedagem ADD FOREIGN KEY (id_funcionario) REFERENCES funcionario(id);");

    if (mysql_errno(servidor)==0) {
        cout<< "Tabela HOSPEDAGEM Criada com Sucesso!\n";
    } else {
        cout<<"\nErro na Criação da tabela no BD "<< mysql_errno(servidor) << ", Mensagem: " << mysql_error(servidor)<<endl;
        exit(1);
    }

    //criando a estrutura da tabela de serviços
    mysql_query(servidor, "CREATE TABLE IF NOT EXISTS servicos (id int PRIMARY KEY AUTO_INCREMENT, id_hospedagem int, id_funcionario int, data_entrada date, data_saida date, status varchar(20), valor DECIMAL(6,2))");
    mysql_query(servidor, "ALTER TABLE servicos ADD FOREIGN KEY (id_funcionario) REFERENCES funcionario(id);");
    mysql_query(servidor, "ALTER TABLE servicos ADD FOREIGN KEY (id_hospedagem) REFERENCES hospedagem(id);");
    if (mysql_errno(servidor)==0) {
        cout<< "Tabela SERVIÇO Criada com Sucesso!\n";
    } else {
        cout<<"\nErro na Criação da tabela no BD "<< mysql_errno(servidor) << ", Mensagem: " << mysql_error(servidor)<<endl;
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
// este método geralmente se encontra na biblioteca conio.h
// caso não esteja na biblioteca, use este metodo
    int __BACKGROUND = 0;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color + (__BACKGROUND << 4));
}

void desenharRetangulo (int base, int altura) {
    //Desenhar um retângulo
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
    //Desenhar um retângulo
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

void telaLogin() {
    string login, senha;
    margemTela();
    textcolor(3);
    desenharRetangulo2(50,15,33,7);
    textcolor(2);
    gotoxy(47, 9);
    printf("SISTEMA DE HOTELARIA");
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
        printf("       Aguarde...        ");
        Sleep(500);
        if( !logincheck) {
            textcolor(4);
            gotoxy(47, 12);
            printf("                    ");
            gotoxy(47, 14);
            printf("                    ");
            gotoxy(47, 16);
            printf("LOGIN OU SENHA INCORRETOS");
            gotoxy(47, 17);
            printf("    TENTE NOVAMENTE!");
        } else {
            gotoxy(47, 16);
            printf("  LOGIN E SENHA CORRETOS ");
            gotoxy(47, 17);
            printf("        AGUARDE...       ");

            usuarioAtivoID = f.salvarIDUsuario(servidor, login, senha);
            nomeUsuarioAtivo = login;
        }
    } while (!logincheck);
    gotoxy(0,29);

}

void menuPrincipal() {

}

int main() {
    conectar();
    verificarEstruturaBD();
    setlocale(LC_ALL, "pt_BR_utf8");
    do {//Loop de tela de Login
        telaLogin();
        Sleep(500);
        int opMenu=8;
        do { // Loop de menu principal
            system("CLS");
            margemTela();
            gotoxy(4,0);
            textcolor(3);
            cout << "Usuário:  " << nomeUsuarioAtivo;
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
            cout << "    4 - SERVIÇOS";
            gotoxy(x,y++);
            y++;
            cout << "    5 - HOSPEDAGEM";
            gotoxy(x,y++);
            y++;
            cout << "    6 - RESERVA";
            gotoxy(x,y++);
            y++;
            cout << "    7 - SAIR";
            gotoxy(x,y++);
            y++;
            cout << "    8 - FECHAR PROGRAMA";
            y++;
            gotoxy(x,++y);
            textcolor(1);
            cout << "    Digite a opção desejada: ";
            if (opMenu<1||opMenu>8) {
                gotoxy(45,26);
                textcolor(4);
                cout << "Opção Inválida. Tente Novamente!";
            }
            textcolor(1);
            gotoxy(x+29,y);

            cin >> opMenu;
        } while (opMenu<1||opMenu>8);
    } while (!loginCHK);
    gotoxy(0,29);

    return 0;
}
