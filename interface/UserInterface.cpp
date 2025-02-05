#include "UserInterface.h"

#include "../database/tables/CertidaoImovel.h"
#include "../database/tables/Proprietario.h"
#include "../database/tables/Telefone.h"

void limpar_tela() {
    system("clear||cls");
}

void listarClientesProposta(MYSQL *conn) {
    std::string query = "SELECT inq.nome, inq.cpf FROM inquilinos inq "
            "JOIN propostas p ON inq.id = p.id_inquilino;";

    if (mysql_query(conn, query.c_str())) {
        throw std::runtime_error("Erro ao buscar inquilinos: " + std::string(mysql_error(conn)) + "\n");
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (!res) {
        throw std::runtime_error("Erro ao obter resultados: " + std::string(mysql_error(conn)) + "\n");
    }

    std::cout << "\nInquilinos que já fizeram propostas:\n";
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res))) {
        std::cout << "Nome: " << (row[0] ? row[0] : "NULL")
                << ", CPF: " << (row[1] ? row[1] : "NULL") << "\n";
    }

    mysql_free_result(res);
}

void listarImoveisCadastrados(MYSQL *conn) {
    std::vector<std::shared_ptr<BaseTable> > imoveis = BaseTable::fetchAll(conn, "imoveis");
    int i = 0;
    for (const auto &record: imoveis) {
        auto imovel_it = std::dynamic_pointer_cast<Imovel>(record);
        if (imovel_it) {
            i++;
            std::cout << "\n" << "Imovel " << i << std::endl;
            imovel_it->print_imovel();
            std::cout << "\n";
        }
    }
}

void listar_ofertas_por_imovel(MYSQL *conn) {
    std::string id_imovel;
    std::cout << "Digite o ID do imóvel para listar as ofertas: ";
    std::cin >> id_imovel;

    std::string query = "SELECT p.id, p.valor, p.validade, "
                        "i.cep, i.cidade, i.bairro, i.rua "
                        "FROM propostas p "
                        "JOIN imoveis i ON p.id_imovel = i.id "
                        "WHERE i.id = '" + id_imovel + "';";

    if (mysql_query(conn, query.c_str())) {
        throw std::runtime_error("Erro ao buscar ofertas: " + std::string(mysql_error(conn)) + "\n");
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (!res) {
        throw std::runtime_error("Erro ao obter resultados: " + std::string(mysql_error(conn)) + "\n");
    }

    std::cout << "\nOfertas para o imóvel ID " << id_imovel << ":\n";
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res))) {
        std::cout << "ID da Proposta: " << (row[0] ? row[0] : "NULL") << "\n"
                << "Valor da Proposta: R$" << (row[1] ? row[1] : "NULL") << "\n"
                << "Validade da Proposta: " << (row[2] ? row[2] : "NULL") << "\n"
                << "Endereço Imovel: " << (row[3] ? row[3] : "NULL") << ", "
                << (row[5] ? row[5] : "NULL") << " - "
                << (row[6] ? row[6] : "NULL") << ", "
                << (row[7] ? row[7] : "NULL") << "\n"
                << "-----------------------------\n";
    }

    mysql_free_result(res);
}

void corretor_maior_rendimento(MYSQL *conn) {
    std::string ano;
    std::cout << "Digite o ano para verificar o corretor de maior rendimento: ";
    std::cin >> ano;

    std::string query = "SELECT c.nome, SUM(o.valor_desejado * c.comissao) AS rendimento, c.comissao as comissao "
                        "FROM corretores_autonomos c "
                        "JOIN ofertas o ON c.id = o.id_corretor "
                        "JOIN contratos_alugueis ca ON o.id_imovel = ca.id_imovel "
                        "WHERE YEAR(ca.data_inicio) = '" + ano + "' "
                        "GROUP BY c.id "
                        "ORDER BY rendimento DESC "
                        "LIMIT 1;";

    if (mysql_query(conn, query.c_str())) {
        throw std::runtime_error(
            "Erro ao buscar corretor com maior rendimento: " + std::string(mysql_error(conn)) + "\n");
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (!res) {
        throw std::runtime_error("Erro ao obter resultados: " + std::string(mysql_error(conn)) + "\n");
    }

    MYSQL_ROW row = mysql_fetch_row(res);
    if (row) {
        std::cout << "\nCorretor com maior rendimento em " << ano << ":\n";
        std::cout << "Nome: " << (row[0] ? row[0] : "NULL") << "\n";
        std::cout << "Rendimento: R$" << (row[1] ? row[1] : "0.00") << "\n";
        std::cout << "Comissão: %" << (row[2] ? row[2] : "%0.00") << "\n";
    } else {
        std::cout << "Nenhum corretor obteve rendimento registrado em " << ano << ".\n";
    }

    mysql_free_result(res);
}

void listar_top_tres_imoveis_mais_caros(MYSQL *conn) {
    std::string query = "SELECT i.id, i.cidade, i.bairro, i.rua, i.area_construida, o.valor_desejado "
            "FROM imoveis i "
            "JOIN ofertas o ON i.id = o.id_imovel "
            "ORDER BY o.valor_desejado DESC "
            "LIMIT 3;";

    if (mysql_query(conn, query.c_str())) {
        throw std::runtime_error("Erro ao buscar os imóveis mais caros: " + std::string(mysql_error(conn)) + "\n");
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (!res) {
        throw std::runtime_error("Erro ao obter resultados: " + std::string(mysql_error(conn)) + "\n");
    }

    std::cout << "\nTop 3 imóveis mais caros:\n";
    MYSQL_ROW row;
    int rank = 1;
    while ((row = mysql_fetch_row(res))) {
        std::cout << "Imóvel #" << rank << ":\n";
        std::cout << "ID: " << (row[0] ? row[0] : "NULL") << "\n";
        std::cout << "Cidade: " << (row[1] ? row[1] : "NULL") << "\n";
        std::cout << "Bairro: " << (row[2] ? row[2] : "NULL") << "\n";
        std::cout << "Rua: " << (row[3] ? row[3] : "NULL") << "\n";
        std::cout << "Área Construída: " << (row[4] ? row[4] : "NULL") << " m²\n";
        std::cout << "Valor Desejado: R$" << (row[5] ? row[5] : "0.00") << "\n";
        std::cout << "-----------------------------\n";
        rank++;
    }

    mysql_free_result(res);
}

void inserir_proprietario(MYSQL *conn) {
    std::string cpf, nome, estado_civil;
    std::cout << "Digite o CPF do proprietário: ";
    std::cin >> cpf;
    std::cout << "Digite o nome do proprietário: ";
    std::cin.ignore();
    std::getline(std::cin, nome);
    std::cout << "Digite o estado civil do proprietário: ";
    std::cin >> estado_civil;

    // Armazena telefones antes de inserir
    std::vector<std::string> telefones;
    char resposta_usuario;
    do {
        std::string telefone;
        std::cout << "Digite um telefone do proprietário: ";
        std::cin >> telefone;
        telefones.push_back(telefone);

        std::cout << "Deseja inserir mais telefones? (s/n): ";
        std::cin >> resposta_usuario;
    } while (resposta_usuario == 's');

    // Armazena imóveis e certidões antes de inserir
    struct ImovelTemp {
        std::string cep, cidade, bairro, rua, complemento, num_registro;
        int num_comodos, num_vagas;
        float area_construida;
    };

    std::vector<ImovelTemp> imoveis;
    do {
        ImovelTemp imovel;
        std::cout << "\nRegistro de Imóvel\n";
        std::cout << "Digite o CEP: ";
        std::cin >> imovel.cep;
        std::cout << "Digite a cidade: ";
        std::cin.ignore();
        std::getline(std::cin, imovel.cidade);
        std::cout << "Digite o bairro: ";
        std::getline(std::cin, imovel.bairro);
        std::cout << "Digite a rua: ";
        std::getline(std::cin, imovel.rua);
        std::cout << "Digite o complemento: ";
        std::getline(std::cin, imovel.complemento);
        std::cout << "Digite o número de cômodos: ";
        std::cin >> imovel.num_comodos;
        std::cout << "Digite o número de vagas: ";
        std::cin >> imovel.num_vagas;
        std::cout << "Digite a área construída (m²): ";
        std::cin >> imovel.area_construida;
        std::cout << "Digite o número de registro do imóvel: ";
        std::cin >> imovel.num_registro;

        imoveis.push_back(imovel);

        std::cout << "Deseja inserir mais imóveis? (s/n): ";
        std::cin >> resposta_usuario;
    } while (resposta_usuario == 's');

    std::cout << "\nDeseja confirmar a inserção dos dados? (s/n): ";
    std::cin >> resposta_usuario;
    if (resposta_usuario != 's') {
        std::cout << "Operação cancelada.\n";
        return;
    }

    // **INSERINDO OS DADOS NO BANCO**

    Proprietario *proprietario = insert_proprietario(conn, cpf, nome, estado_civil);
    std::string id_proprietario = proprietario->getAttribute("id");

    for (const std::string &telefone: telefones) {
        TelefoneProprietario telefone_proprietario;
        telefone_proprietario.set_numero(telefone);
        telefone_proprietario.set_id_proprietario(id_proprietario);
        telefone_proprietario.insert(conn);
    }

    for (const ImovelTemp &imovel: imoveis) {
        Imovel *novo_imovel = insert_imovel(conn, imovel.cep, imovel.cidade, imovel.bairro, imovel.rua,
                                            imovel.complemento,
                                            imovel.num_comodos, imovel.num_vagas, imovel.area_construida);
        std::string id_imovel = novo_imovel->getAttribute("id");

        CertidaoImovel certidao;
        certidao.set_id_prop(id_proprietario);
        certidao.set_id_imovel(id_imovel);
        certidao.set_num_registro(imovel.num_registro);
        certidao.insert(conn);
    }

    std::cout << "\nProprietário, imóveis e registros foram inseridos com sucesso!\n";
}

void inserir_imovel(MYSQL *conn) {
    std::string id_proprietario;
    std::string cpf_proprietario;
    char escolha;

    // Permitir busca por ID ou CPF
    std::cout << "Deseja buscar o proprietário pelo (1) ID ou (2) CPF? ";
    std::cin >> escolha;

    Proprietario *proprietario = nullptr;

    if (escolha == '1') {
        std::cout << "Digite o ID do proprietário: ";
        std::cin >> id_proprietario;
        proprietario = new Proprietario();
        proprietario->setAttribute("id", id_proprietario);
        proprietario->fetchFromDB(conn);
    } else if (escolha == '2') {
        std::cout << "Digite o CPF do proprietário: ";
        std::cin >> cpf_proprietario;

        std::string query = "SELECT id FROM proprietarios WHERE cpf = '" + cpf_proprietario + "';";
        if (mysql_query(conn, query.c_str())) {
            std::cerr << "Erro ao buscar proprietário: " << mysql_error(conn) << "\n";
            return;
        }

        MYSQL_RES *res = mysql_store_result(conn);
        if (!res) {
            std::cerr << "Erro ao obter resultados: " << mysql_error(conn) << "\n";
            return;
        }

        MYSQL_ROW row = mysql_fetch_row(res);
        if (!row) {
            std::cout << "Proprietário com CPF " << cpf_proprietario << " não encontrado.\n";
            mysql_free_result(res);
            return;
        }

        id_proprietario = row[0];
        mysql_free_result(res);

        proprietario = new Proprietario();
        proprietario->setAttribute("id", id_proprietario);
        proprietario->fetchFromDB(conn);
    } else {
        std::cout << "Opção inválida. Operação cancelada.\n";
        return;
    }

    std::string cep, cidade, bairro, rua, complemento, num_registro;
    int num_comodos, num_vagas;
    float area_construida;

    std::cout << "\nRegistro de Imóvel\n";
    std::cout << "Digite o CEP: ";
    std::cin >> cep;
    std::cout << "Digite a cidade: ";
    std::cin.ignore();
    std::getline(std::cin, cidade);
    std::cout << "Digite o bairro: ";
    std::getline(std::cin, bairro);
    std::cout << "Digite a rua: ";
    std::getline(std::cin, rua);
    std::cout << "Digite o complemento: ";
    std::getline(std::cin, complemento);
    std::cout << "Digite o número de cômodos: ";
    std::cin >> num_comodos;
    std::cout << "Digite o número de vagas: ";
    std::cin >> num_vagas;
    std::cout << "Digite a área construída (m²): ";
    std::cin >> area_construida;
    std::cout << "Digite o número de registro do imóvel: ";
    std::cin >> num_registro;

    // Confirmação antes da inserção
    std::cout << "\nDeseja confirmar a inserção do imóvel e da certidão? (s/n): ";
    char confirmacao;
    std::cin >> confirmacao;
    if (confirmacao != 's') {
        std::cout << "Operação cancelada.\n";
        delete proprietario;
        return;
    }

    // **INSERINDO OS DADOS NO BANCO**
    Imovel *imovel = insert_imovel(conn, cep, cidade, bairro, rua, complemento, num_comodos, num_vagas,
                                   area_construida);
    std::string id_imovel = imovel->getAttribute("id");

    CertidaoImovel certidao;
    certidao.set_id_prop(id_proprietario);
    certidao.set_id_imovel(id_imovel);
    certidao.set_num_registro(num_registro);
    certidao.insert(conn);

    std::cout << "\nImóvel e certidão cadastrados com sucesso!\n";

    // Libera memória
    delete proprietario;
}


void inserir_novo_registro(MYSQL *conn) {
    int opcao;
    do {
        std::cout << "\n==== INSERIR NOVO REGISTRO ====\n";
        std::cout << "1. Inserir Proprietário\n";
        std::cout << "2. Inserir Inquilino\n";
        std::cout << "3. Inserir Corretor Autônomo\n";
        std::cout << "4. Inserir Imóvel\n";
        std::cout << "5. Inserir Oferta\n";
        std::cout << "6. Inserir Proposta\n";
        std::cout << "7. Inserir Contrato de Aluguel\n";
        std::cout << "8. Inserir Fiador\n";
        std::cout << "9. Inserir Certidão de Imóvel\n";
        std::cout << "10. Inserir Telefone de Proprietário\n";
        std::cout << "11. Inserir Telefone de Inquilino\n";
        std::cout << "12. Inserir Telefone de Corretor\n";
        std::cout << "13. Inserir Telefone de Fiador\n";
        std::cout << "14. Inserir Visita\n";
        std::cout << "0. Voltar\n";
        std::cout << "Escolha uma opção: ";
        std::cin >> opcao;

        switch (opcao) {
            case 1: inserir_proprietario(conn);
                break;
            case 4: inserir_imovel(conn);
                break;
            /*case 2: inserirInquilino(conn);
                break;
            case 3: inserirCorretorAutonomo(conn);
                break;
            case 4: inserirImovel(conn);
                break;
            case 5: inserirOferta(conn);
                break;
            case 6: inserirProposta(conn);
                break;
            case 7: inserirContratoAluguel(conn);
                break;
            case 8: inserirFiador(conn);
                break;
            case 9: inserirCertidaoImovel(conn);
                break;
            case 10: inserirTelefoneProprietario(conn);
                break;
            case 11: inserirTelefoneInquilino(conn);
                break;
            case 12: inserirTelefoneCorretor(conn);
                break;
            case 13: inserirTelefoneFiador(conn);
                break;
            case 14: inserirVisita(conn);
                break;
                */
            case 0: std::cout << "Voltando ao menu principal...\n";
                break;
            default: std::cout << "Opção inválida! Tente novamente.\n";
        }
    } while (opcao != 0);
}

void menu(MYSQL *conn) {
    int opcao;
    do {
        std::cout << "\n==== SISTEMA IMOBILIÁRIO ====\n";
        std::cout << "1. Listar inquilinos que fizeram propostas\n";
        std::cout << "2. Listar imóveis cadastrados\n";
        std::cout << "3. Listar ofertas de um imóvel\n";
        std::cout << "4. Corretor com maior rendimento\n";
        std::cout << "5. Listar os 3 imóveis mais caros\n";
        std::cout << "6. Inserir novo registro\n";
        std::cout << "7. Atualizar registro\n";
        std::cout << "8. Deletar registro\n";
        std::cout << "9. Limpar tela\n";
        std::cout << "0. Sair\n";
        std::cout << "Escolha uma opção: ";
        std::cin >> opcao;

        switch (opcao) {
            case 1: listarClientesProposta(conn);
                break;
            case 2: listarImoveisCadastrados(conn);
                break;
            case 3: listar_ofertas_por_imovel(conn);
                break;
            case 4: corretor_maior_rendimento(conn);
                break;
            case 5: listar_top_tres_imoveis_mais_caros(conn);
                break;
            case 6: inserir_novo_registro(conn);
                break;
            /*
            case 7: atualizarRegistro(conn); break;
            case 8: deletarRegistro(conn); break;*/
            case 9: limpar_tela();
                break;
            case 0: std::cout << "Saindo...\n";
                break;
            default: limpar_tela();
                std::cout << "Opção inválida!\n";
        }
    } while (opcao != 0);
}
