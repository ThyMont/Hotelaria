#include <iostream>
#include <mysql.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



using namespace std;

class hospede {
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

    void carregar (){
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

    void cadastrarHospedeBD(MYSQL *servidor, string nome, string cpf, string celular, string telefone, string data_nascimento, string nacionalidade, string cidade, string uf ) {
        mysql_select_db(servidor,"hoteldb");
        if (mysql_errno(servidor)==0) {
            string query = "INSERT INTO hospede (nome, cpf, celular, telefone, data_nascimento, nacionalidade, cidade, uf ) VALUES('"+(nome)+"', '"+(cpf)+"', '"+(celular)+"','"+(telefone)+"', '"+(data_nascimento)+"', '"+(nacionalidade)+"', '"+(cidade)+"', '"+(uf)+"');";
            mysql_query(servidor,query.c_str());

            if (mysql_errno(servidor)==0) {
                textcolor(10);
                gotoxy(40,20);
                cout << "Hospede cadastrado com sucesso.";
                gotoxy(40,21);
                cout << "Retornando ao menu de HOSPEDE";
                for(int i = 0; i<5; i++) {
                    cout<<".";
                    Sleep(500);
                }
            }
            getchar();
        } else {
            gotoxy(20,16);
            cout<<"\nErro ao acessar o banco de dados "<< mysql_errno(servidor) << ", Mensagem: " << mysql_error(servidor)<<endl;
            exit(1);
        }
    }


    void cadastrarHospede(MYSQL *servidor) {
        string nome, cpf, celular, telefone, data_nascimento, nacionalidade, cidade, uf ;
        int confirmarCadastro; // Resposta de confirmação
        do {
            carregar();
            system("CLS");
            margemTela();
            gotoxy(4,0);
            textcolor(3);
            gotoxy(40,3);
            textcolor(15);
            cout << "- - - -    CADASTRAR HOSPEDE    - - - -";
            gotoxy(40,6);
            textcolor(12);
            cout << "    NOME: ";
            gotoxy(40,7);
            cout << "    CPF: ";
            gotoxy(40,8);
            cout << "    CELULAR: ";
            gotoxy(40,9);
            cout << "    TELEFONE: ";
            gotoxy(40,10);
            cout << "    DATA DE NASCIMENTO: ";
            gotoxy(40,11);
            cout << "    NACIONALIDADE: ";
            gotoxy(40,12);
            cout << "    CIDADE: ";
            gotoxy(40,13);
            cout << "    UF: ";
            gotoxy(40,14);

            textcolor(11);
            gotoxy(50,6);
            cin>>nome;
            gotoxy(49,7);
            cin>>cpf;
            gotoxy(53,8);
            cin>>celular;
            gotoxy(54,9);
            cin>>telefone;
            gotoxy(64,10);
            cin>>data_nascimento;
            gotoxy(59,11);
            cin>>nacionalidade;
            gotoxy(52,12);
            cin>>cidade;
            gotoxy(48,13);
            cin>>uf;

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
                    cadastrarHospedeBD(servidor, nome, cpf, celular, telefone, data_nascimento, nacionalidade, cidade, uf);
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
                    cout << "Retornando ao menu de HOSPEDE";
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

    void procurarPorCPFBD(MYSQL *servidor, string cpf) {
        mysql_select_db(servidor,"hoteldb");
        if (mysql_errno(servidor)==0) {
            string query = "SELECT id, nome, cpf from hospede WHERE cpf LIKE \'%%"+cpf+"%%\';";
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
                    cout << ++i<<". ID: "<<row[0] << " Nome: "<< row[1] <<"\t CPF: "<< row[2] << endl;
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

    void localizarPorCPF(MYSQL *servidor) {
        int op;
        do {
            system("CLS");
            margemTela();
            gotoxy(4,0);
            textcolor(3);
            gotoxy(35,3);
            textcolor(15);
            cout << "- - - -    LOCALIZAR HOSPEDE POR CPF   - - - -";
            gotoxy(35,8);
            textcolor(12);
            cout << "DIGITE O CPF DESEJADO: ";
            textcolor(11);
            gotoxy(35,10);
            string cpf;
            cin>>cpf;
            procurarPorCPFBD(servidor, cpf);

            cin>> op;
        } while(op!=1);
    }

    void procurarPorNomeBD(MYSQL *servidor, string nome) {
        mysql_select_db(servidor,"hoteldb");
        if (mysql_errno(servidor)==0) {
            string query = "SELECT id, nome, cpf from hospede WHERE nome LIKE \'%%"+nome+"%%\';";
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
                    cout << ++i<<". ID: "<<row[0] << " Nome: "<< row[1] <<"\t CPF: "<< row[2] << endl;
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
            cout << "- - - -    LOCALIZAR HOSPEDE POR NOME   - - - -";
            gotoxy(35,8);
            textcolor(12);
            cout << "DIGITE O NOME DESEJADO: ";
            textcolor(11);
            gotoxy(35,10);
            string nome;
            cin>>nome;
            procurarPorNomeBD(servidor, nome);

            cin>> op;
        } while(op!=1);
    }

    void editarHospede(MYSQL *servidor) {
        int op;
        system("CLS");
        margemTela();
        gotoxy(4,0);
        textcolor(3);
        gotoxy(10,3);
        textcolor(15);
        cout << "- - - -     EDITAR HOSPEDE     - - - -";
        gotoxy(10,5);
        textcolor(12);
        cout << "INFORME A ID DO HOSPEDE: ";
        textcolor(11);
        gotoxy(10,7);
        string id;
        cin>>id;

        string query = "SELECT id, nome, cpf, celular, telefone, uf, data_nascimento, cidade, nacionalidade from hospede WHERE id LIKE '%"+id+"%';";
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
                cout << ++i<< ". ID: " << row[0] << " Nome: " << row[1] <<" CPF: "<< row[2] << " Celular: "<< row[3]<< endl;
                gotoxy(x+4,y++);
                cout  << "Telefone: " << row[4] << "UF: " << row[5] << "DN: " << row[6] << "Cidade: " << row[7]<< endl;
                gotoxy(x+4,y++);
                cout  << "nacionalidade: " <<row[8] <<endl;
                Sleep(500);
            }

                if(i>0) {
                    gotoxy(x,y+4);
                    textcolor(13);
                    cout << "Selecione a opcao a editar: ";
                    gotoxy(x,y+5);
                    cout << "1. NOME: ";
                    gotoxy(x,y+6);
                    cout << "2. CPF: ";
                    gotoxy(x,y+7);
                    cout << "3. CELULAR: ";
                    gotoxy(x,y+8);
                    cout << "4. TELEFONE: ";
                    gotoxy(x,y+9);
                    cout << "5. DATA DE NASCIMENTO: ";
                    gotoxy(x,y+10);
                    cout << "6. NACIONALIDADE: ";
                    gotoxy(x,y+11);
                    cout << "7. CIDADE: ";
                    gotoxy(x,y+12);
                    cout << "8. UF: ";
                    gotoxy(x,y+13);
                    cout << "9. CANCELAR ";
                    gotoxy(x,y+14);
                } else {
                    textcolor(13);
                    gotoxy(x,y+5);
                    cout << "Digite 9 para CANCELAR ";
                    gotoxy(x,y+6);
                }
                do {
                cin>> op;
                if (i>0) {
                    string editado;
                    switch (op) {
                    case 1: {
                        gotoxy(x,++y);
                        cout << "Digite o novo NOME: ";
                        cin >> editado;
                        mysql_select_db(servidor,"hoteldb");
                        if (mysql_errno(servidor)==0) {
                            string query = "UPDATE hospede SET nome='"+(editado)+"' WHERE id = "+(id)+";";
                            mysql_query(servidor,query.c_str());
                            if (mysql_errno(servidor)==0) {
                                gotoxy(x,++y);
                                cout << "Hospede editado com sucesso. Pressione a tecla ENTER para continuar.";
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
                        cout << "Digite o novo CPF: ";
                        cin >> editado;
                        mysql_select_db(servidor,"hoteldb");
                        if (mysql_errno(servidor)==0) {
                            string query = "UPDATE hospede SET cpf='"+(editado)+"' WHERE id = "+(id)+";";
                            mysql_query(servidor,query.c_str());
                            if (mysql_errno(servidor)==0) {
                                gotoxy(x,++y);
                                cout << "Hospede editado com sucesso.\nPressione a tecla ENTER para continuar.";
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
                        gotoxy(x,++y);
                        cout << "Digite o novo celular: ";
                        cin >> editado;
                        mysql_select_db(servidor,"hoteldb");
                        if (mysql_errno(servidor)==0) {
                            string query = "UPDATE hospede SET celular='"+(editado)+"' WHERE id = "+(id)+";";
                            mysql_query(servidor,query.c_str());
                            if (mysql_errno(servidor)==0) {
                                gotoxy(x,++y);
                                cout << "Hospede editado com sucesso. Pressione a tecla ENTER para continuar.";
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
                        cout << "Digite o novo telefone: ";
                        cin >> editado;
                        mysql_select_db(servidor,"hoteldb");
                        if (mysql_errno(servidor)==0) {
                            string query = "UPDATE hospede SET telefone='"+(editado)+"' WHERE id = "+(id)+";";
                            mysql_query(servidor,query.c_str());
                            if (mysql_errno(servidor)==0) {
                                gotoxy(x,++y);
                                cout << "Hospede editado com sucesso. Pressione a tecla ENTER para continuar.";
                            }
                            getchar();
                        } else {
                            gotoxy(x,++y);
                            cout<<"Erro ao acessar o banco de dados "<< mysql_errno(servidor) << ", Mensagem: " << mysql_error(servidor)<<endl;
                            exit(1);
                        }
                        break;
                    }
                    case 5: {
                        gotoxy(x,++y);
                        cout << "Digite o novo NOME: ";
                        cin >> editado;
                        mysql_select_db(servidor,"hoteldb");
                        if (mysql_errno(servidor)==0) {
                            string query = "UPDATE hospede SET nome='"+(editado)+"' WHERE id = "+(id)+";";
                            mysql_query(servidor,query.c_str());
                            if (mysql_errno(servidor)==0) {
                                gotoxy(x,++y);
                                cout << "Hospede editado com sucesso. Pressione a tecla ENTER para continuar.";
                            }
                            getchar();
                        } else {
                            gotoxy(x,++y);
                            cout<<"Erro ao acessar o banco de dados "<< mysql_errno(servidor) << ", Mensagem: " << mysql_error(servidor)<<endl;
                            exit(1);
                        }
                        break;
                    }
                    case 6: {
                        gotoxy(x,++y);
                        cout << "Digite a nova DATA DE NASCIMENTO: ";
                        cin >> editado;
                        mysql_select_db(servidor,"hoteldb");
                        if (mysql_errno(servidor)==0) {
                            string query = "UPDATE hospede SET data_nascimento ='"+(editado)+"' WHERE id = "+(id)+";";
                            mysql_query(servidor,query.c_str());
                            if (mysql_errno(servidor)==0) {
                                gotoxy(x,++y);
                                cout << "Hospede editado com sucesso. Pressione a tecla ENTER para continuar.";
                            }
                            getchar();
                        } else {
                            gotoxy(x,++y);
                            cout<<"Erro ao acessar o banco de dados "<< mysql_errno(servidor) << ", Mensagem: " << mysql_error(servidor)<<endl;
                            exit(1);
                        }
                        break;
                    }
                    case 7: {
                        gotoxy(x,++y);
                        cout << "Digite a nova CIDADE: ";
                        cin >> editado;
                        mysql_select_db(servidor,"hoteldb");
                        if (mysql_errno(servidor)==0) {
                            string query = "UPDATE hospede SET cidade ='"+(editado)+"' WHERE id = "+(id)+";";
                            mysql_query(servidor,query.c_str());
                            if (mysql_errno(servidor)==0) {
                                gotoxy(x,++y);
                                cout << "Hospede editado com sucesso. Pressione a tecla ENTER para continuar.";
                            }
                            getchar();
                        } else {
                            gotoxy(x,++y);
                            cout<<"Erro ao acessar o banco de dados "<< mysql_errno(servidor) << ", Mensagem: " << mysql_error(servidor)<<endl;
                            exit(1);
                        }
                        break;
                    }
                    case 8: {
                        gotoxy(x,++y);
                        cout << "Digite a nova NACIONALIDADE: ";
                        cin >> editado;
                        mysql_select_db(servidor,"hoteldb");
                        if (mysql_errno(servidor)==0) {
                            string query = "UPDATE hospede SET NACIONALIDADE ='"+(editado)+"' WHERE id = "+(id)+";";
                            mysql_query(servidor,query.c_str());
                            if (mysql_errno(servidor)==0) {
                                gotoxy(x,++y);
                                cout << "Hospede editado com sucesso. Pressione a tecla ENTER para continuar.";
                            }
                            getchar();
                        } else {
                            gotoxy(x,++y);
                            cout<<"Erro ao acessar o banco de dados "<< mysql_errno(servidor) << ", Mensagem: " << mysql_error(servidor)<<endl;
                            exit(1);
                        }
                        break;
                    }
                    case 9: {
                        gotoxy(x,y+3);
                        textcolor(3);
                        cout << "Edicao cancelada! Voltando, aguarde ";
                        for(int i = 1; i<5; i++) {
                            Sleep(500);
                            cout << ".";
                        }
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
                    case 9: {
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
            } while(op<1||op>9);
        }
    }


    void excluirHospede(MYSQL *servidor) {
        int op;
        do {
            system("CLS");
            margemTela();
            gotoxy(4,0);
            textcolor(3);
            gotoxy(10,3);
            textcolor(15);
            cout << "- - - -     EXCLUIR HOSPEDE     - - - -";
            gotoxy(10,5);
            textcolor(12);
            cout << "INFORME A ID DO HOSPEDE: ";
            textcolor(11);
            gotoxy(10,7);
            string id;
            cin>>id;

            string query = "SELECT id, nome, cpf, celular, telefone, uf, data_nascimento, cidade, nacionalidade from hospede WHERE id LIKE '%"+id+"%';";
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
                    cout << ++i<< ". ID: " << row[0] << " Nome: " << row[1] <<" CPF: "<< row[2] << " Celular: "<< row[3]<< endl;
                    gotoxy(x+4,y++);
                    cout  << "Telefone: " << row[4] << "UF: " << row[5] << "DN: " << row[6] << "Cidade: " << row[7]<< endl;
                    gotoxy(x+4,y++);
                    cout  << "nacionalidade: " <<row[8] <<endl;
                    Sleep(500);
                }
                if(i>0) {
                    gotoxy(x,++y);
                    textcolor(13);
                    cout << "SELECIONE A OPÇÃO DESEJADA: ";
                    gotoxy(x,++y);
                    cout << "1. EXCLUIR HOSPEDE: ";
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
                            string query = "DELETE FROM hospede WHERE id = "+(id)+";";
                            mysql_query(servidor,query.c_str());

                            if (mysql_errno(servidor)==0) {
                                gotoxy(x,++y);
                                cout << "Hospede excluido com sucesso. Aguarde para continuar.";
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


    void contarhospedes(MYSQL *servidor) {
        system("CLS");
        margemTela();
        gotoxy(4,0);
        textcolor(3);
        gotoxy(40,5);
        textcolor(15);
        cout << "- - - -     LISTAR HOSPEDES POR UF    - - - -";

        mysql_select_db(servidor,"hoteldb");
        if (mysql_errno(servidor)==0) {
            string query = "SELECT COUNT(*) FROM hospede;";
            mysql_query(servidor,query.c_str());
            gotoxy(40,10);
            textcolor(6);
            cout << "Contando";
            for(int i = 1; i<7; i++) {
                Sleep(500);
                cout << ".";
            }
            int x = 40, y = 15;
            if (mysql_errno(servidor)==0) {

                Sleep(1);
                MYSQL_RES* res = mysql_use_result(servidor);
                MYSQL_ROW row;
                textcolor(15);
                while( ( row = mysql_fetch_row(res)) != NULL ) {
                    gotoxy(x,y++);
                    cout <<"Total de hospedes cadastrados: "<<row[0] <<  endl;
                    Sleep(500);
                }
                y++;

                gotoxy(x,y+2);
                textcolor(5);
                cout << "Pressione ENTER para continuar";
            } else {
                gotoxy(x,y+2);
                cout<<"\nErro ao acessar o banco de dados "<< mysql_errno(servidor) << ", Mensagem: " << mysql_error(servidor)<<endl;
                exit(1);
            }
            getchar();
        }
    }
    void listarporUF(MYSQL *servidor) {
        system("CLS");
        margemTela();
        gotoxy(4,0);
        textcolor(3);
        gotoxy(40,3);
        textcolor(15);
        cout << "- - - -     LISTAR HOSPEDES POR UF    - - - -";

        mysql_select_db(servidor,"hoteldb");
        if (mysql_errno(servidor)==0) {
            string query = "SELECT id, nome, uf from hospede ORDER BY uf;";
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
                    cout << ++i<<". ID: "<<row[0] << " Nome: "<< row[1] <<"\t CPF: "<< row[2] << endl;
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
    }

};
