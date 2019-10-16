#include <iostream>
#include <mysql.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

class funcionario {
public:
    bool fazerLogin (MYSQL *servidor, string login, string senha) {
        string query = "SELECT id FROM funcionario WHERE nome='"+login+"' AND senha = '"+ senha+"';";
        mysql_query(servidor,query.c_str());
        MYSQL_RES* res = mysql_use_result(servidor);
        MYSQL_ROW row;
        int i = 0;
        while( ( row = mysql_fetch_row(res)) != NULL ) {
            i++;
        }
        if (i>=1) {
            return true;

        } else {
            return false;
        }
    }

    string salvarIDUsuario (MYSQL *servidor, string login, string senha) {
        //Registra ID do usuário após o Login
        string query = "SELECT id FROM funcionario WHERE nome='"+login+"' AND senha = '"+ senha+"';";
        mysql_query(servidor,query.c_str());
        MYSQL_RES* res = mysql_use_result(servidor);
        MYSQL_ROW row;
        while( ( row = mysql_fetch_row(res)) != NULL ) {
            return row[0];
        }
    }

    void cabecalho() {
        cout<< " --- HOTEL DO FIM DO MUNDO ---\n";
        cout<< "   Quintos dos Infernos, 666\n";
        cout<< "   Telefone: (66) 66669-6969\n";
        cout<< " -----------------------------\n\n";

    }
    void cadastrarFuncionarioBD(MYSQL *servidor, string nome, string cpf, string celular, string telefone, string uf, string data_nascimento, string cidade, string nacionalidade, string salario ) {
        mysql_select_db(servidor,"hoteldb");
        if (mysql_errno(servidor)==0) {
            string query = "INSERT INTO funcionario (nome, cpf, celular, telefone, uf, data_nascimento, cidade, nacionalidade, salario ) VALUES('"+(nome)+"', '"+(cpf)+"', '"+(celular)+"','"+(telefone)+"', '"+(uf)+"', '"+(data_nascimento)+"', '"+(cidade)+"', '"+(nacionalidade)+"', '"+(salario)+"');";
            mysql_query(servidor,query.c_str());

            if (mysql_errno(servidor)==0) {
                cout << "Hóspede cadastrado com sucesso.\nPressione a tecla ENTER para continuar.";
            }
            getchar();
        } else {
            cout<<"\nErro ao acessar o banco de dados "<< mysql_errno(servidor) << ", Mensagem: " << mysql_error(servidor)<<endl;
            exit(1);
        }
    }

    void cadastrarFuncionario(MYSQL *servidor) {
        string nome, cpf, celular, telefone, uf, data_nascimento, cidade, nacionalidade, salario;
        int confirma; // Resposta de confirmação
        do {
            system("CLS");
            cout<< "--- Cadastrar Funcionário ---\n";
            cout<< "Digite o nome do Funcionário:";
            cin>>nome;
            cout<< "Digite o CPF do Funcionário:";
            cin>>cpf;
            cout<< "Digite o Celular do Funcionário:";
            cin>>celular;
            cout<< "Digite o telefone do Funcionário:";
            cin>>telefone;
            cout<< "Digite a data de nascimento do Funcionário:";
            cin>>data_nascimento;
            cout<< "Digite a nacionalidade do Funcionário:";
            cin>>nacionalidade;
            cout<< "Digite a cidade do Funcionário:";
            cin>>cidade;
            cout<< "Digite a UF do Funcionário:";
            cin>>uf;
            cout<< "Digite o Salário do Funcionário:";
            cin>>salario;
            do {
                cout<< "\n\nVocê confirma os dados acima?\n Digite 1 para SIM, 2 para NÃO, 3 para CANCELAR CADASTRO: ";
                cin>>confirma;
                switch (confirma) {
                case 1: {
                    cadastrarFuncionarioBD(servidor, nome, cpf, celular, telefone, uf, data_nascimento, cidade, nacionalidade, salario);
                    break;
                }
                case 2: {
                    cout<< "\n\nReiniciando cadastro";
                    for(int i = 0; i<5; i++) {
                        cout<<".";
                        Sleep(500);
                        break;
                    }
                }
                case 3: {
                    cout<<"\n\nCadastro cancelado com sucesso!\n\n Pressione ENTER para retornar à tela inicial";
                    getchar();
                    break;
                }
                default: {
                    cout<<"\n\nOpção inválida. Tente novamente! \n\n Pressione ENTER para continuar";
                    getchar();
                }
                }
            } while (confirma<1 && confirma > 3);
        } while (confirma != 1 && confirma!= 3);
    }

    void procurarPorCPFBD(MYSQL *servidor, string cpf) {
        mysql_select_db(servidor,"hoteldb");
        if (mysql_errno(servidor)==0) {
            string query = "SELECT id, nome, cpf  from funcionario WHERE cpf LIKE '%"+cpf+"%';";
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
            string query = "SELECT id, nome, cpf from funcionario WHERE nome LIKE \'%%"+nome+"%%\';";
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

    void pesquisarFuncionario(MYSQL *servidor) {
        system("CLS");
        int op;
        do {
            cout<< "---  PROCURAR HÓSPEDE  ---\n";
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
            }
        } while(op<1&&op>3);
    }

    void editarFuncionario(MYSQL *servidor) {
        system("CLS");
        mysql_select_db(servidor,"hoteldb");
        string id;
        if (mysql_errno(servidor)==0) {
            cout << "\n---  EDITAR Hóspede  ---\n";
            cout << "\n\nDigite a ID do hóspede a ser editado: ";
            cin >> id;
            string query = "SELECT id, nome,cpf from funcionario WHERE id LIKE '%"+id+"%';";
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
            string query = "UPDATE funcionario SET nome='"+(nome)+"' WHERE id = "+(id)+";";
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


    void excluirFuncionario(MYSQL *servidor) {
        system("CLS");
        mysql_select_db(servidor,"hoteldb");
        string id;
        if (mysql_errno(servidor)==0) {
            cout << "---  EXCLUIR Hóspede  ---\n";
            cout << "\n\nDigite a ID do hóspede a ser excluído: ";
            cin >> id;
            string query = "SELECT id, nome,cpf from funcionario WHERE id LIKE '%"+id+"%';";
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
            string query = "UPDATE funcionario SET nome='"+(nome)+"' WHERE id = "+(id)+";";
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

    void contarFuncionarios(MYSQL *servidor) {
        system("CLS");
        cout << "---  Contagem total de hóspedes  ---\n";
        mysql_select_db(servidor,"hoteldb");
        if (mysql_errno(servidor)==0) {
            string query = "SELECT COUNT(*) FROM funcionario;";
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

            string query = "SELECT id, nome, uf from funcionario ORDER BY uf;";
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

    void verificarCadastros(MYSQL *servidor) {

        mysql_select_db(servidor,"hoteldb");
        if (mysql_errno(servidor)==0) {
            string query = "SELECT COUNT(*) FROM funcionario;";
            mysql_query(servidor,query.c_str());
        }
        int i;
        if (mysql_errno(servidor)==0) {
            MYSQL_RES* res = mysql_use_result(servidor);
            MYSQL_ROW row;
            while( ( row = mysql_fetch_row(res)) != NULL ) {
                cout<< row;
                i = (int)row[0]-48;
            }
        }
        cout << i;
        if (i==0) {

            cadastrarFuncionario(servidor);
        }
        getchar();
    }

};
