#include <iostream>
#include <mysql.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


using namespace std;


class suite {
private:
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

public:
    //                          numero SMALLINT UNIQUE NOT NULL , ramal varchar(11), vagas SMALLINT(2)  , ocupado varchar(1) DEFAULT ('N'), data_entrada date, manutencao varchar(1) DEFAULT ('N'), preco DECIMAL(6,2)
    void cadastrarSuiteBD(MYSQL *servidor, string numero, string ramal, string vagas, string preco ) {
        mysql_select_db(servidor,"hoteldb");
        if (mysql_errno(servidor)==0) {
            string query = "INSERT INTO funcionario (numero, ramal, vagas, data_entrada, preço) VALUES('"+(numero)+"', '"+(ramal)+"', '"+(vagas)+"','"+(preco)+"');";
            mysql_query(servidor,query.c_str());

            if (mysql_errno(servidor)==0) {
                textcolor(10);
                gotoxy(40,20);
                cout << "SUITE cadastrada com sucesso.";
                gotoxy(40,21);
                carregar();
            }
            getchar();
        } else {
            cout<<"\nErro ao acessar o banco de dados "<< mysql_errno(servidor) << ", Mensagem: " << mysql_error(servidor)<<endl;
            exit(1);
        }
    }

    void cadastrarSuite(MYSQL *servidor) {
        string numero, ramal, vagas, preco, statu;
        int confirmarCadastro; // Resposta de confirmação

        do {
            carregar();
            system("CLS");
            margemTela();
            gotoxy(4,0);
            textcolor(3);
            gotoxy(40,3);
            textcolor(15);
            cout << "- - - -    CADASTRAR SUITE    - - - -";
            gotoxy(40,6);
            textcolor(12);
            cout << "    NUMERO: ";
            gotoxy(40,7);
            cout << "    RAMAL: ";
            gotoxy(40,8);
            cout << "    VAGAS: ";
            gotoxy(40,9);
            cout << "    PRECO: ";
            gotoxy(40,10);

            textcolor(11);
            gotoxy(50,6);
            cin>>numero;
            gotoxy(49,7);
            cin>>ramal;
            gotoxy(53,8);
            cin>>vagas;
            gotoxy(54,9);
            cin>>preco;


            do {
                textcolor(13);
                gotoxy(20,17);
                cout<< "Voce confirma os dados acima?";
                gotoxy(20,18);
                cout<< "Digite 1 para CONFIRMAR, 2 para REINICIAR, 3 para CANCELAR CADASTRO:      ";
                gotoxy(88,18);
                cin>>confirmarCadastro;
                switch (confirmarCadastro) {
                case 1: {
                    cadastrarSuiteBD(servidor, numero, ramal, vagas, preco );
                    carregar();
                    break;
                }
                case 2: {
                    textcolor(10);
                    gotoxy(40,19);
                    cout<< "Reiniciando cadastro";
                    carregar();
                    break;
                }
                case 3: {
                    textcolor(10);
                    gotoxy(40,19);
                    cout<<"Cadastro cancelado com sucesso!";
                    gotoxy(40,20);
                    cout << "Retornando ao menu de SUITES";
                    carregar();
                    break;
                }
                default: {
                    cout<<"\n\nOpção inválida. Tente novamente! \n\n Pressione ENTER para continuar";
                }
                }
            } while ((confirmarCadastro<1 && confirmarCadastro > 3));
        } while ((confirmarCadastro<1 && confirmarCadastro > 3)||confirmarCadastro == 2);
    }

void procurarPorNumeroBD(MYSQL *servidor, string numero) {
        mysql_select_db(servidor,"hoteldb");
        if (mysql_errno(servidor)==0) {
            string query = "SELECT * from hospede WHERE numero LIKE \'%%"+numero+"%%\';";
            mysql_query(servidor,query.c_str());
            gotoxy(40,11);
            textcolor(6);
            cout << "Pesquisando";
            for(int i = 1; i<5; i++) {
                Sleep(500);
                cout << ".";
            }

            if (mysql_errno(servidor)==0) {
                int x = 35, y = 14;
                gotoxy(40,12);
                textcolor(14);
                cout << "Pesquisa realizada com sucesso!";
                Sleep(1);
                MYSQL_RES* res = mysql_use_result(servidor);
                MYSQL_ROW row;
                int i = 0;
                textcolor(15);
                while( ( row = mysql_fetch_row(res)) != NULL ) {
                    gotoxy(x,y++);
                    cout << ++i<<". ID: "<<row[0] << " Numero: "<< row[1] <<"\t Vagas: "<< row[2] << endl;
                    Sleep(500);
                    gotoxy(x+5,y++);
                    cout << "Status: "<<row[3] << "\tPreco"<< row[4] << endl;
                }
                y++;
                gotoxy(x,++y);
                textcolor(13);
                cout << "Foram encontrados " << i << " resultado(s)";

                gotoxy(x,y+2);
                textcolor(5);
                cout << "Digite 1 para RETORNAR ou 2 para PESQUISAR NOVAMENTE ";
            }
        } else {
            cout<<"\nErro ao acessar o banco de dados "<< mysql_errno(servidor) << ", Mensagem: " << mysql_error(servidor)<<endl;
            exit(1);
        }
    }

    void localizarPorNumero(MYSQL *servidor) {
        int op;
        do {
            system("CLS");
            margemTela();
            gotoxy(4,0);
            textcolor(3);
            gotoxy(35,3);
            textcolor(15);
            cout << "- - - -    LOCALIZAR SUITE POR NUMERO   - - - -";
            gotoxy(35,8);
            textcolor(12);
            cout << "DIGITE O NUMERO DA SUITE DESEJADA: ";
            textcolor(11);
            gotoxy(35,10);
            string numero;
            cin>>numero;
            procurarPorNumeroBD(servidor, numero);

            cin>> op;
        } while(op!=1);
    }
};
