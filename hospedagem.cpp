#include <iostream>
#include <mysql.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



using namespace std;


class hospedagem {
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

    void ocuparSuite(MYSQL *servidor, string id) {
        string query = "UPDATE suite SET ocupacao = 'ocupado' WHERE id = "+id+"';";
        mysql_query(servidor,query.c_str());
    }

public:

    void cadastrarHospedagemBD(MYSQL *servidor, string idHospede, string idSuite, string dataEntrada) {
        mysql_select_db(servidor,"hoteldb");
        if (mysql_errno(servidor)==0) {
            string query = "INSERT INTO hospedagem (id_hospede,	id_suite, data_entrada) VALUES('"+(idHospede)+"', '"+(idSuite)+"', '"+(dataEntrada)+"');";
            mysql_query(servidor,query.c_str());

            if (mysql_errno(servidor)==0) {
                textcolor(10);
                gotoxy(40,20);
                cout << "Hospedagem cadastrada com sucesso.";
                gotoxy(40,21);
                cout << "Retornando ao menu de HOSPEDAGEM";

            }
            getchar();
        } else {
            gotoxy(20,16);
            cout<<"\nErro ao acessar o banco de dados "<< mysql_errno(servidor) << ", Mensagem: " << mysql_error(servidor)<<endl;
            exit(1);
        }
    }

    void cadastrarHospedagem (MYSQL *servidor) {
        string idHospede, idSuite, dataEntrada;
        int confirmarCadastro;
        do {
            carregar();
            system("CLS");
            margemTela();
            gotoxy(4,0);
            textcolor(3);
            gotoxy(40,3);
            textcolor(15);
            cout << "- - - -    CADASTRAR HOSPEDAGEM    - - - -";
            gotoxy(40,6);
            textcolor(12);
            cout << "    ID HOSPEDE: ";
            gotoxy(40,7);
            cout << "    ID SUITE: ";
            gotoxy(40,8);
            cout << "    DATA DE ENTRADA: ";
            gotoxy(40,9);

            textcolor(11);
            gotoxy(56,6);
            cin>>idHospede;
            gotoxy(52,7);
            cin>>idSuite;
            gotoxy(61,8);
            cin>>dataEntrada;

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
                    cadastrarHospedagemBD(servidor, idHospede, idSuite, dataEntrada);
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
                    cout << "Retornando ao menu de FUNCIONARIO";
                    carregar();
                    break;
                }
                default: {
                    cout<<"\n\nOp��o inv�lida. Tente novamente! \n\n Pressione ENTER para continuar";
                }
                }
            } while ((confirmarCadastro<1 && confirmarCadastro > 3));
        } while ((confirmarCadastro<1 && confirmarCadastro > 3)||confirmarCadastro == 2);
    }

    void localizarPorNomeBD(MYSQL *servidor, string nome) {
        mysql_select_db(servidor,"hoteldb");
        if (mysql_errno(servidor)==0) {
            string query = "SELECT A.NOME, B.data_entrada , C.numero, C.preco FROM hospede AS A JOIN hospedagem AS B JOIN suite AS C ON A.id = B.id_hospede AND c.id = b.id_suite WHERE a.nome LIKE \'%%"+nome+"%%\';";
            mysql_query(servidor,query.c_str());
            gotoxy(40,11);
            textcolor(6);
            cout << "Pesquisando";
            for(int i = 1; i<5; i++) {
                Sleep(500);
                cout << ".";
            }

            if (mysql_errno(servidor)==0) {
                int x = 25, y = 14;
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
                    cout << ++i<<". NOME: "<<row[0] << "  Data de Entrada: "<< row[1] <<"  Numero: "<< row[2] <<"  Preco: R$"<< row[2]<< endl;
                    Sleep(500);
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

    void localizarPorNome(MYSQL *servidor) {
        int op;
        do {
            system("CLS");
            margemTela();
            gotoxy(4,0);
            textcolor(3);
            gotoxy(35,3);
            textcolor(15);
            cout << "- - - -    LOCALIZAR HOSPEDAGEM POR NOME   - - - -";
            gotoxy(35,8);
            textcolor(12);
            cout << "DIGITE O NOME DESEJADO: ";
            textcolor(11);
            gotoxy(35,10);
            string nome;
            cin>>nome;
            localizarPorNomeBD(servidor, nome);
            cin>> op;
        } while(op!=1);
    }

    void CalcularConta(MYSQL *servidor, string idHospedagem) {

    }

    void encerrarHospedagem(MYSQL *servidor) {

        system("CLS");
        margemTela();
        gotoxy(4,0);
        textcolor(3);
        gotoxy(35,3);
        textcolor(15);
        cout << "- - - -    ENCERRAR HOSPEDAGEM   - - - -";
        gotoxy(35,8);
        textcolor(12);
        cout << "DIGITE A ID DA HOSPEDAGEM A SER ENCERRADA: ";
        textcolor(11);
        gotoxy(35,10);
        string id;
        cin>>id;
        mysql_select_db(servidor,"hoteldb");
        if (mysql_errno(servidor)==0) {
            string query = "SELECT A.NOME, SUM(B.valor) FROM `vendas` as B JOIN HOSPEDE AS A JOIN hospedagem AS C ON A.id = c.id_hospede AND c.id = b.id_hospedagem WHERE c.id  = "+id+";";
            mysql_query(servidor,query.c_str());
            gotoxy(40,11);
            textcolor(6);
            cout << "Pesquisando";
            for(int i = 1; i<5; i++) {
                Sleep(500);
                cout << ".";
            }

            if (mysql_errno(servidor)==0) {
                int x = 25, y = 14;
                gotoxy(40,12);
                textcolor(14);
                cout << "Pesquisa realizada com sucesso!";
                Sleep(1);
                MYSQL_RES* res = mysql_use_result(servidor);
                MYSQL_ROW row;
                int i = 0;
                string soma;
                textcolor(15);
                while( ( row = mysql_fetch_row(res)) != NULL ) {
                    gotoxy(x,y++);
                    cout << ++i<<". NOME: "<<row[0] << "  Total: "<< row[1] << endl;
                    soma = row[1];
                    Sleep(500);
                }
                y++;
                gotoxy(x,++y);
                int op;
                do {
                    gotoxy(x,y+2);
                    textcolor(5);
                    cout << "DESEJA ENCERRAR A HOSPEDAGEM? 1 PARA SIM, 2 PARA N�O ";
                    cin >> op;
                } while (op!=1&&op!=2);
                if (op == 1) {
                    string query = "UPDATE hospedagem set conta_final = "+ soma +" WHERE id = "+id+";";
                    mysql_query(servidor,query.c_str());

                    query = "UPDATE vendas set pagamento = PAGO WHERE id = "+id+";";
                    mysql_query(servidor,query.c_str());
                    gotoxy(x,y+3);
                    cout << "Hospedagem Encerrada com sucesso";
                    carregar();
                } else {
                    gotoxy(x,y+3);
                    cout << "Opera��o cancelada";
                    carregar();
                }
            }
        } else {
            cout<<"\nErro ao acessar o banco de dados "<< mysql_errno(servidor) << ", Mensagem: " << mysql_error(servidor)<<endl;
            exit(1);
        }
    }
};
