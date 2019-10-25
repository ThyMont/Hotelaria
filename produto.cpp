#include <iostream>
#include <mysql.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


using namespace std;


class produto {
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
    //
    void cadastrarProdutoBD(MYSQL *servidor, string descricao, string preco ) {
        mysql_select_db(servidor,"hoteldb");
        if (mysql_errno(servidor)==0) {
            string query = "INSERT INTO produto (descricao, preço) VALUES('"+(descricao)+"', '"+(preco)+"');";
            mysql_query(servidor,query.c_str());

            if (mysql_errno(servidor)==0) {
                textcolor(10);
                gotoxy(40,20);
                cout << "PRODUTO cadastrado com sucesso.";
                gotoxy(40,21);

            }
            getchar();
        } else {
            cout<<"\nErro ao acessar o banco de dados "<< mysql_errno(servidor) << ", Mensagem: " << mysql_error(servidor)<<endl;
            exit(1);
        }
    }

    void cadastrarProduto(MYSQL *servidor) {
        string descricao, preco;
        int confirmarCadastro; // Resposta de confirmação

        do {
            carregar();
            system("CLS");
            margemTela();
            gotoxy(4,0);
            textcolor(3);
            gotoxy(40,3);
            textcolor(15);
            cout << "- - - -    CADASTRAR PRODUTO    - - - -";
            gotoxy(40,6);
            textcolor(12);
            cout << "    DESCRICAO: ";
            gotoxy(40,7);
            cout << "    PRECO: ";
            gotoxy(40,8);

            textcolor(11);
            gotoxy(50,6);
            cin>>descricao;
            gotoxy(49,7);
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
                    cadastrarProdutoBD(servidor,descricao, preco );
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
                    cout << "Retornando ao menu de PRODUTOS";
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

    void procurarPorNomeBD(MYSQL *servidor, string descricao) {
        mysql_select_db(servidor,"hoteldb");
        if (mysql_errno(servidor)==0) {
            string query = "SELECT * from produto WHERE descricao LIKE \'%%"+descricao+"%%\';";
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
                    cout << ++i<<". ID: "<<row[0] << " Descricao: "<< row[1] <<"\t Preco: "<< row[2] << endl;
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

    void localizarPorDescricao(MYSQL *servidor) {
        int op;
        do {
            system("CLS");
            margemTela();
            gotoxy(4,0);
            textcolor(3);
            gotoxy(35,3);
            textcolor(15);
            cout << "- - - -    LOCALIZAR PRODUTO POR DESCRICAO   - - - -";
            gotoxy(35,8);
            textcolor(12);
            cout << "DIGITE O NOME DA PRODUTO DESEJADA: ";
            textcolor(11);
            gotoxy(35,10);
            string descricao;
            cin>>descricao;
            procurarPorNomeBD(servidor, descricao);

            cin>> op;
        } while(op!=1);
        carregar();
    }

    void listarPorDescricao(MYSQL *servidor) {
        system("CLS");
        margemTela();
        gotoxy(4,0);
        textcolor(3);
        gotoxy(40,3);
        textcolor(15);
        cout << "- - - -     LISTAR PRODUTOS POR DESCRICAO    - - - -";

        mysql_select_db(servidor,"hoteldb");
        if (mysql_errno(servidor)==0) {
            string query = "SELECT * from produto ORDER BY descricao;";
            mysql_query(servidor,query.c_str());
            gotoxy(40,6);
            textcolor(6);
            cout << "Pesquisando";
            for(int i = 1; i<5; i++) {
                Sleep(500);
                cout << ".";
            }

            if (mysql_errno(servidor)==0) {
                int x = 35, y = 8;
                gotoxy(40,7);
                textcolor(14);
                cout << "Pesquisa realizada com sucesso!";
                Sleep(1);
                MYSQL_RES* res = mysql_use_result(servidor);
                MYSQL_ROW row;
                int i = 0;
                textcolor(15);
                while( ( row = mysql_fetch_row(res)) != NULL ) {
                    gotoxy(x,y++);
                    cout << ++i<<". ID: "<<row[0] << " Descricao: "<< row[1] <<"\t Preco: "<< row[2] << endl;
                    Sleep(500);
                }
                y++;
                gotoxy(x,++y);
                textcolor(13);
                cout << "Foram encontrados " << i << " resultado(s)";

                gotoxy(x,y+2);
                textcolor(5);
                cout << "Pressione ENTER para continuar";
            }
        } else {
            cout<<"\nErro ao acessar o banco de dados "<< mysql_errno(servidor) << ", Mensagem: " << mysql_error(servidor)<<endl;
            exit(1);
        }
        getchar();
        carregar();
    }

    void editarProduto(MYSQL *servidor) {
        int op;
        system("CLS");
        margemTela();
        gotoxy(4,0);
        textcolor(3);
        gotoxy(10,3);
        textcolor(15);
        cout << "- - - -     EDITAR PRODUTO     - - - -";
        gotoxy(10,5);
        textcolor(12);
        cout << "INFORME A ID DO PRODUTO: ";
        textcolor(11);
        gotoxy(10,7);
        string id;
        cin>>id;

        string query = "SELECT * from produto WHERE id LIKE '%"+id+"%';";
        mysql_query(servidor,query.c_str());
        gotoxy(10,9);
        textcolor(6);
        cout << "Aguarde";
        for(int i = 1; i<5; i++) {
            Sleep(500);
            cout << ".";
        }

        if (mysql_errno(servidor)==0) {
            int x = 10, y = 10;
            MYSQL_RES* res = mysql_use_result(servidor);
            MYSQL_ROW row;
            int i = 0;
            textcolor(15);
            while( ( row = mysql_fetch_row(res)) != NULL ) {
                gotoxy(x,y++);
                cout << ++i<<". ID: "<<row[0] << " Descricao: "<< row[1] <<"\t Preco: "<< row[2] << endl;
                Sleep(500);
            }

            if(i>0) {
                gotoxy(x,y+4);
                textcolor(13);
                cout << "Selecione a opcao a editar: ";
                gotoxy(x,y+5);
                cout << "1. DESCRICAO: ";
                gotoxy(x,y+6);
                cout << "2. PRECO: ";
                gotoxy(x,y+7);
                cout << "3. CANCELAR: ";
                gotoxy(x,y+8);
            } else {
                textcolor(13);
                gotoxy(x,y+5);
                cout << "Digite 3 para CANCELAR ";
                gotoxy(x,y+6);
            }
            do {
                cin>> op;
                if (i>0) {
                    string editado;
                    switch (op) {
                    case 1: {
                        gotoxy(x,++y);
                        cout << "Digite a nova DESCRICAO: ";
                        cin >> editado;
                        mysql_select_db(servidor,"hoteldb");
                        if (mysql_errno(servidor)==0) {
                            string query = "UPDATE produto SET numero='"+(editado)+"' WHERE id = "+(id)+";";
                            mysql_query(servidor,query.c_str());
                            if (mysql_errno(servidor)==0) {
                                gotoxy(x,++y);
                                cout << "Produto editado com sucesso. Pressione a tecla ENTER para continuar.";
                            }
                            getchar();
                        } else {
                            gotoxy(x,++y);
                            cout<<"Erro ao acessar o banco de dados "<< mysql_errno(servidor) << ", Mensagem: " << mysql_error(servidor)<<endl;
                            exit(1);
                        }
                        break;
                    }
                    case 2: {
                        gotoxy(x,++y);
                        cout << "Digite o novo preco: ";
                        cin >> editado;
                        mysql_select_db(servidor,"hoteldb");
                        if (mysql_errno(servidor)==0) {
                            string query = "UPDATE produto SET preco='"+(editado)+"' WHERE id = "+(id)+";";
                            mysql_query(servidor,query.c_str());
                            if (mysql_errno(servidor)==0) {
                                gotoxy(x,++y);
                                cout << "Produto editada com sucesso. Pressione a tecla ENTER para continuar.";
                            }
                            getchar();
                        } else {
                            gotoxy(x,++y);
                            cout<<"Erro ao acessar o banco de dados "<< mysql_errno(servidor) << ", Mensagem: " << mysql_error(servidor)<<endl;
                            exit(1);
                        }
                        break;
                    }
                    case 4: {
                        gotoxy(x,++y);
                        cout << "Digite o novo status: ";
                        cin >> editado;
                        mysql_select_db(servidor,"hoteldb");
                        if (mysql_errno(servidor)==0) {
                            string query = "UPDATE produto SET telefone='"+(editado)+"' WHERE id = "+(id)+";";
                            mysql_query(servidor,query.c_str());
                            if (mysql_errno(servidor)==0) {
                                gotoxy(x,++y);
                                cout << "Produto editada com sucesso. Pressione a tecla ENTER para continuar.";
                            }
                            getchar();
                        } else {
                            gotoxy(x,++y);
                            cout<<"Erro ao acessar o banco de dados "<< mysql_errno(servidor) << ", Mensagem: " << mysql_error(servidor)<<endl;
                            exit(1);
                        }
                        break;
                    }
                    case 3: {
                        gotoxy(x,y+3);
                        textcolor(3);
                        cout << "Edicao cancelada! Voltando, aguarde ";
                        carregar();
                        break;
                    }
                    default: {
                        gotoxy(x,y+3);
                        textcolor(3);
                        cout << "Opçao invalida! Tente novamente:  ";
                        break;
                    }

                    }
                } else {
                    switch (op) {
                    case 5: {
                        gotoxy(x,y+3);
                        textcolor(3);
                        cout << "Edicao cancelada! Voltando, aguarde ";
                        carregar();
                        break;
                    }
                    default: {
                        gotoxy(x,y+3);
                        textcolor(3);
                        cout << "Opção invalida! Tente novamente ";
                        break;
                    }
                    }
                }
            } while(op<1||op>3);
        }
    }

    void excluirProduto(MYSQL *servidor) {
        int op;
        do {
            system("CLS");
            margemTela();
            gotoxy(4,0);
            textcolor(3);
            gotoxy(10,3);
            textcolor(15);
            cout << "- - - -     EXCLUIR PRODUTO     - - - -";
            gotoxy(10,5);
            textcolor(12);
            cout << "INFORME A ID DO PRODUTO: ";
            textcolor(11);
            gotoxy(10,7);
            string id;
            cin>>id;

            string query = "SELECT * from produto WHERE id LIKE '%"+id+"%';";
            mysql_query(servidor,query.c_str());
            gotoxy(10,9);
            textcolor(6);
            cout << "Aguarde";
            for(int i = 1; i<5; i++) {
                Sleep(500);
                cout << ".";
            }

            if (mysql_errno(servidor)==0) {
                int x = 10, y = 10;
                MYSQL_RES* res = mysql_use_result(servidor);
                MYSQL_ROW row;
                int i = 0;
                textcolor(15);
                while( ( row = mysql_fetch_row(res)) != NULL ) {
                    gotoxy(x,y++);
                    cout << ++i<<". ID: "<<row[0] << " Descricao: "<< row[1] <<"\t Preco: "<< row[2] << endl;
                    Sleep(500);
                }
                if(i>0) {
                    gotoxy(x,++y);
                    textcolor(13);
                    cout << "SELECIONE A OPÇÃO DESEJADA: ";
                    gotoxy(x,++y);
                    cout << "1. EXCLUIR PRODUTO: ";
                    gotoxy(x,++y);
                    cout << "2. PROCURAR NOVAMENTE: ";
                    gotoxy(x,++y);
                    cout << "3. CANCELAR: ";

                } else {
                    gotoxy(x,++y);
                    textcolor(13);
                    cout << "SELECIONE A OPÇÃO DESEJADA: ";
                    gotoxy(x,++y);
                    cout << "2. PROCURAR NOVAMENTE: ";
                    gotoxy(x,++y);
                    cout << "3. CANCELAR: ";
                }
                gotoxy(x,++y);
                cin>> op;

                if (i>0) {
                    switch (op) {
                    case 1: {
                        if (mysql_errno(servidor)==0) {
                            string query = "DELETE FROM produto WHERE id = "+(id)+";";
                            mysql_query(servidor,query.c_str());

                            if (mysql_errno(servidor)==0) {
                                gotoxy(x,++y);
                                cout << "Produto excluida com sucesso. Aguarde para continuar.";
                                for(int i = 1; i<5; i++) {
                                    Sleep(500);
                                    cout << ".";
                                }
                            }
                        } else {
                            gotoxy(x,++y);
                            cout<<"\nErro ao acessar o banco de dados "<< mysql_errno(servidor) << ", Mensagem: " << mysql_error(servidor)<<endl;
                            exit(1);
                        }
                        break;
                    }
                    case 2: {
                        gotoxy(x,++y);
                        cout << "Reiniciando a pesquisa. Aguarde para continuar.";
                        for(int i = 1; i<5; i++) {
                            Sleep(500);
                            cout << ".";
                        }
                        break;
                    }
                    case 3: {
                        gotoxy(x,++y);
                        cout << "Cancelando a exclusão. Aguarde para continuar.";
                        for(int i = 1; i<5; i++) {
                            Sleep(500);
                            cout << ".";
                        }
                        break;
                    }
                    default: {
                        gotoxy(x,++y);
                        cout << "Opção inválida. Aguarde para continuar.";
                        for(int i = 1; i<5; i++) {
                            Sleep(500);
                            cout << ".";
                        }
                        break;
                    }
                    }
                } else {
                    switch (op) {
                    case 2: {
                        gotoxy(x,++y);
                        cout << "Reiniciando a pesquisa. Aguarde para continuar.";
                        for(int i = 1; i<5; i++) {
                            Sleep(500);
                            cout << ".";
                        }
                        break;
                    }
                    case 3: {
                        gotoxy(x,++y);
                        cout << "Reiniciando a pesquisa. Aguarde para continuar.";
                        for(int i = 1; i<5; i++) {
                            Sleep(500);
                            cout << ".";
                        }
                        break;
                    }
                    default: {
                        gotoxy(x,++y);
                        cout << "Opção inválida. Aguarde para continuar.";
                        for(int i = 1; i<5; i++) {
                            Sleep(500);
                            cout << ".";
                        }
                        break;
                    }
                    }
                }
            }
        } while (op!=3&&op!=1);
    }
};
