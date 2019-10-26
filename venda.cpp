#include <iostream>
#include <mysql.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



using namespace std;


class venda {
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

    void ocuparSuite(MYSQL *servidor, string id) {
        string query = "UPDATE suite SET ocupacao = 'ocupado' WHERE id = "+id+"';";
        mysql_query(servidor,query.c_str());
    }

public:

    void registrarVendaBD(MYSQL *servidor, string idHospedagem, string idProduto, string dataVenda) {
        mysql_select_db(servidor,"hoteldb");
        if (mysql_errno(servidor)==0) {
            string query = "INSERT INTO vendas (id_hospedagem, id_produto, data_venda, valor) VALUES ('"+(idHospedagem)+"', '"+(idProduto)+"', '"+(dataVenda)+"',(SELECT  A.preco from produtos AS A JOIN vendas AS B WHERE a.id = b.id_produto LIMIT 1));";
            mysql_query(servidor,query.c_str());

            mysql_query(servidor,query.c_str());
            if (mysql_errno(servidor)==0) {
                textcolor(10);
                gotoxy(40,20);
                cout << "Venda cadastrada com sucesso.";
                gotoxy(40,21);
                cout << "Retornando ao menu de VENDA";

            }
            getchar();
        } else {
            gotoxy(20,16);
            cout<<"\nErro ao acessar o banco de dados "<< mysql_errno(servidor) << ", Mensagem: " << mysql_error(servidor)<<endl;
            exit(1);
        }
    }

    void registrarVenda (MYSQL *servidor) {
        string idHospedagem, idProduto, dataVenda;
        int confirmarCadastro;
        do {
            carregar();
            system("CLS");
            margemTela();
            gotoxy(4,0);
            textcolor(3);
            gotoxy(40,3);
            textcolor(15);
            cout << "- - - -    CADASTRAR VENDA    - - - -";
            gotoxy(40,6);
            textcolor(12);
            cout << "    ID HOSPEDAGEM: ";
            gotoxy(40,7);
            cout << "    ID PRODUTO: ";
            gotoxy(40,8);
            cout << "    DATA DE VENDA: ";
            gotoxy(40,9);

            textcolor(11);
            gotoxy(56,6);
            cin>>idHospedagem;
            gotoxy(52,7);
            cin>>idProduto;
            gotoxy(61,8);
            cin>>dataVenda;

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
                    registrarVendaBD(servidor, idHospedagem, idProduto, dataVenda);
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
                    cout<<"\n\nOpção inválida. Tente novamente! \n\n Pressione ENTER para continuar";
                }
                }
            } while ((confirmarCadastro<1 && confirmarCadastro > 3));
        } while ((confirmarCadastro<1 && confirmarCadastro > 3)||confirmarCadastro == 2);
    }

    void cancelarVenda(MYSQL *servidor) {

        system("CLS");
        margemTela();
        gotoxy(4,0);
        textcolor(3);
        gotoxy(35,3);
        textcolor(15);
        cout << "- - - -    ENCERRAR VENDA   - - - -";
        gotoxy(35,8);
        textcolor(12);
        cout << "DIGITE A ID DA VENDA A SER CANCELADA: ";
        textcolor(11);
        gotoxy(35,10);
        string id;
        cin>>id;
        mysql_select_db(servidor,"hoteldb");
        if (mysql_errno(servidor)==0) {
            string query = "SELECT A.id, B.descricao, A.data_venda, B.preco FROM vendas as A JOIN produtos AS B ON B.id = A.id_produto  WHERE A.id  = "+id+";";
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
                string id;
                textcolor(15);
                while( ( row = mysql_fetch_row(res)) != NULL ) {
                    gotoxy(x,y++);
                    cout << "ID: "<< row[0]<<". Produto: "<<row[1] << "  Data de Venda: "<< row[2]<<" Preço: R$" << row[3] << endl;
                    id = row[0];
                    Sleep(500);
                }
                y++;
                gotoxy(x,++y);
                int op;
                do {
                    gotoxy(x,y+2);
                    textcolor(5);
                    cout << "DESEJA CANCELAR A VENDA? 1 PARA SIM, 2 PARA NÃO ";
                    cin >> op;
                } while (op!=1&&op!=2);
                if (op == 1) {
                    query = "UPDATE vendas set pagamento = CANCELADO WHERE id = "+id+";";
                    mysql_query(servidor,query.c_str());
                    gotoxy(x,y+3);
                    cout << "Venda Cancelada com sucesso";
                    carregar();
                } else {
                    gotoxy(x,y+3);
                    cout << "Operação cancelada";
                    carregar();
                }
            }
        } else {
            cout<<"\nErro ao acessar o banco de dados "<< mysql_errno(servidor) << ", Mensagem: " << mysql_error(servidor)<<endl;
            exit(1);
        }
    }
};
