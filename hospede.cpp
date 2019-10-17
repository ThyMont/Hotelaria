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
                    break;
                }
                case 2: {
                    textcolor(10);
                    gotoxy(40,19);
                    cout<< "Reiniciando cadastro";
                    for(int i = 0; i<5; i++) {
                        cout<<".";
                        Sleep(500);;
                    }
                    break;
                }
                case 3: {
                    textcolor(10);
                    gotoxy(40,19);
                    cout<<"Cadastro cancelado com sucesso!";
                    gotoxy(40,20);
                    cout << "Retornando ao menu de HOSPEDE";
                    for(int i = 0; i<5; i++) {
                        cout<<".";
                        Sleep(500);
                    }
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
            string query = "SELECT id, nome, cpf  from hospede WHERE cpf LIKE '%"+cpf+"%';";
            mysql_query(servidor,query.c_str());

            cout << "Pesquisando";
            for(int i = 1; i<5; i++) {
                Sleep(500);
                cout << ".";
            }

            if (mysql_errno(servidor)==0) {
                cout << "\nPesquisa realizada com sucesso!\n";
                Sleep(1);
                MYSQL_RES* res = mysql_use_result(servidor);
                MYSQL_ROW row;
                int i = 0;
                while( ( row = mysql_fetch_row(res)) != NULL ) {
                    cout <<"\n\t"<< ++i<<". ID: "<<row[0] << " Nome: "<< row[1] <<"\t CPF: "<< row[2] << endl;
                    Sleep(500);
                }
                cout << "Foram encontrados " << i << " resultado(s)";
                getchar();
            }
        } else {
            cout<<"\nErro ao acessar o banco de dados "<< mysql_errno(servidor) << ", Mensagem: " << mysql_error(servidor)<<endl;
            exit(1);
        }

        cout<<"\nPresssione ENTER para continuar";
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
                int x = 40, y = 14;
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
                    cout <<"\n\t"<< ++i<<". ID: "<<row[0] << " Nome: "<< row[1] <<"\t CPF: "<< row[2] << endl;
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
            gotoxy(40,3);
            textcolor(15);
            cout << "- - - -    LOCALIZAR HOSPEDE POR NOME   - - - -";
            gotoxy(40,8);
            textcolor(12);
            cout << "DIGITE O NOME DESEJADO: ";
            textcolor(11);
            gotoxy(40,10);
            string nome;
            cin>>nome;
            procurarPorNomeBD(servidor, nome);

            cin>> op;

            /*cout<< "---  PROCURAR HÓSPEDE  ---\n";
            cout<< "\nDigite 1 para pesquisar por NOME\nDigite 2 para pesquisar por CPF\nDigite 3 para cancelar";
            cin>>op;
            switch(op) {
            case 1: {
                string nome;
                cout<< "\nDigite o nome desejado:\n";
                cin>>nome;
                procurarPorNomeBD(servidor, nome);
                break;

            }
            case 2: {
                string cpf;
                cout<< "\nDigite o cpf desejado:\n";
                cin>>cpf;
                procurarPorNomeBD(servidor, cpf);
                break;

            }
            case 3: {
                cout<<"Operação Cancelada";
            }
            default: {
                cout<<"Opção inválida. Tente novamente";
            }
            }*/
        } while(op!=1);
    }

    void editarHospede(MYSQL *servidor) {
        system("CLS");
        mysql_select_db(servidor,"hoteldb");
        string id;
        if (mysql_errno(servidor)==0) {
            cout << "\n---  EDITAR Hóspede  ---\n";
            cout << "\n\nDigite a ID do hóspede a ser editado: ";
            cin >> id;
            string query = "SELECT id, nome,cpf from hospede WHERE id LIKE '%"+id+"%';";
            mysql_query(servidor,query.c_str());

            cout << "Aguarde";
            for(int i = 1; i<10; i++) {
                Sleep(500);
                cout << ".";
            }

            if (mysql_errno(servidor)==0) {
                cout << "\nPronto!\n";
                Sleep(1);
                MYSQL_RES* res = mysql_use_result(servidor);
                MYSQL_ROW row;
                int i = 0;
                while( ( row = mysql_fetch_row(res)) != NULL ) {
                    cout <<"\n\t"<< ++i<<". ID: "<<row[0] << "Nome: "<< row[1] <<"\t CPF: "<< row[2] << endl;
                    Sleep(500);
                }
                cout << "Foram encontrados " << i << " resultado(s)";
                getchar();
            }

        } else {
            cout<<"\nErro ao acessar o banco de dados "<< mysql_errno(servidor) << ", Mensagem: " << mysql_error(servidor)<<endl;
            exit(1);
        }
        string nome;
        cout<< "\nEditar usuário com a id:" <<id<<"\n";
        cout<< "Editando o nome do hóspede:\n";

        cout<< "Digite o novo nome do hóspede:";
        cin>>nome;

        mysql_select_db(servidor,"hoteldb");
        if (mysql_errno(servidor)==0) {
            string query = "UPDATE hospede SET nome='"+(nome)+"' WHERE id = "+(id)+";";
            mysql_query(servidor,query.c_str());

            if (mysql_errno(servidor)==0) {
                cout << "Hóspede editado com sucesso.\nPressione a tecla ENTER para continuar.";
            }
            getchar();
        } else {
            cout<<"\nErro ao acessar o banco de dados "<< mysql_errno(servidor) << ", Mensagem: " << mysql_error(servidor)<<endl;
            exit(1);
        }

        cout<<"\nPresssione ENTER para continuar";
    }


    void excluirHospede(MYSQL *servidor) {
        system("CLS");
        mysql_select_db(servidor,"hoteldb");
        string id;
        if (mysql_errno(servidor)==0) {

            cout << "---  EXCLUIR Hóspede  ---\n";
            cout << "\n\nDigite a ID do hóspede a ser excluído: ";
            cin >> id;
            string query = "SELECT id, nome,cpf from hospede WHERE id LIKE '%"+id+"%';";
            mysql_query(servidor,query.c_str());

            cout << "Aguarde";
            for(int i = 1; i<10; i++) {
                Sleep(500);
                cout << ".";
            }

            if (mysql_errno(servidor)==0) {
                cout << "\nPronto!\n";
                Sleep(1);
                MYSQL_RES* res = mysql_use_result(servidor);
                MYSQL_ROW row;
                int i = 0;
                while( ( row = mysql_fetch_row(res)) != NULL ) {
                    cout <<"\n\t"<< ++i<<". ID: "<<row[0] << "Nome: "<< row[1] <<"\t CPF: "<< row[2] << endl;
                    Sleep(500);
                }
                cout << "Foram encontrados " << i << " resultado(s)";
                getchar();
            }

        } else {
            cout<<"\nErro ao acessar o banco de dados "<< mysql_errno(servidor) << ", Mensagem: " << mysql_error(servidor)<<endl;
            exit(1);
        }
        string nome;
        cout<< "\nExcluir usuário com a id:" <<id<<"\n";
        cout<< "Confirma a exclusão?\n";

        cout<< "Digite o novo nome do hóspede:";
        cin>>nome;

        mysql_select_db(servidor,"hoteldb");
        if (mysql_errno(servidor)==0) {
            string query = "UPDATE hospede SET nome='"+(nome)+"' WHERE id = "+(id)+";";
            mysql_query(servidor,query.c_str());

            if (mysql_errno(servidor)==0) {
                cout << "Hóspede editado com sucesso.\nPressione a tecla ENTER para continuar.";
            }
            getchar();
        } else {
            cout<<"\nErro ao acessar o banco de dados "<< mysql_errno(servidor) << ", Mensagem: " << mysql_error(servidor)<<endl;
            exit(1);
        }
    }

    void contarhospedes(MYSQL *servidor) {
        system("CLS");
        cout << "---  Contagem total de hóspedes  ---\n";
        mysql_select_db(servidor,"hoteldb");
        if (mysql_errno(servidor)==0) {
            string query = "SELECT COUNT(*) FROM hospede;";
            mysql_query(servidor,query.c_str());

            cout << "Contando";
            for(int i = 1; i<10; i++) {
                Sleep(500);
                cout << ".";
            }
        }

        if (mysql_errno(servidor)==0) {
            cout << "\nPronto!\n";
            Sleep(1);
            MYSQL_RES* res = mysql_use_result(servidor);
            MYSQL_ROW row;
            while( ( row = mysql_fetch_row(res)) != NULL ) {
                cout <<" Total de hóspedes cadastrados: "<<row[0] <<  endl;
            }

            cout<< "Pressione ENTER para continuar";
            getchar();
        }
    }

    void listarporUF(MYSQL *servidor) {
        mysql_select_db(servidor,"hoteldb");
        if (mysql_errno(servidor)==0) {
            system("CLS");
            cout << "---  Listando hóspedes por UF  ---\n";

            string query = "SELECT id, nome, uf from hospede ORDER BY uf;";
            mysql_query(servidor,query.c_str());

            cout << "\nListando";
            for(int i = 1; i<10; i++) {
                Sleep(500);
                cout << ".";
            }

            if (mysql_errno(servidor)==0) {
                cout << "\nPesquisa realizada com sucesso!\n";
                Sleep(1);
                MYSQL_RES* res = mysql_use_result(servidor);
                MYSQL_ROW row;
                int i = 0;
                while( ( row = mysql_fetch_row(res)) != NULL ) {
                    cout <<"\n\t"<< ++i<<". ID: "<<row[0] << " Nome: "<< row[1] <<"\t UF: "<< row[2] << endl;
                    Sleep(500);
                    getchar();
                }
                cout << "Foram encontrados " << i << " resultado(s)";
                getchar();
            }
        } else {
            cout<<"\nErro ao acessar o banco de dados "<< mysql_errno(servidor) << ", Mensagem: " << mysql_error(servidor)<<endl;
            exit(1);
        }

        cout<<"\nPresssione ENTER para continuar";
        getchar();
    }

};
