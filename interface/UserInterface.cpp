#include "UserInterface.h"

void limpar_tela() {
    system("clear||cls");
}

void listarClientesProposta(MYSQL* conn) {
    std::string query = "SELECT inq.nome, inq.cpf FROM inquilinos inq "
                        "JOIN propostas p ON inq.id = p.id_inquilino;";

    if (mysql_query(conn, query.c_str())) {
        throw std::runtime_error("Erro ao buscar inquilinos: " + std::string(mysql_error(conn)) + "\n");
    }

    MYSQL_RES* res = mysql_store_result(conn);
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

void listarImoveisCadastrados(MYSQL* conn) {
    std::vector<std::shared_ptr<BaseTable>> imoveis = BaseTable::fetchAll(conn, "imoveis");
    int i = 0;
    for (const auto& record : imoveis) {
        auto imovel_it = std::dynamic_pointer_cast<Imovel>(record);
        if (imovel_it) {
            i++;
            std::cout << "\n" << "Imovel " << i << std::endl;
            imovel_it->print_imovel();
            std::cout << "\n";

        }
    }
}

void listar_ofertas_por_imovel(MYSQL* conn) {
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

    MYSQL_RES* res = mysql_store_result(conn);
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

void corretor_maior_rendimento(MYSQL* conn) {
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
        throw std::runtime_error("Erro ao buscar corretor com maior rendimento: " + std::string(mysql_error(conn)) + "\n");
    }

    MYSQL_RES* res = mysql_store_result(conn);
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

void menu(MYSQL* conn) {
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

            case 1: listarClientesProposta(conn); break;
            case 2: listarImoveisCadastrados(conn); break;
            case 3: listar_ofertas_por_imovel(conn); break;
            case 4: corretor_maior_rendimento(conn); break;
            /*
            case 5: listarTresImoveisMaisCaros(conn); break;
            case 6: inserirNovoRegistro(conn); break;
            case 7: atualizarRegistro(conn); break;
            case 8: deletarRegistro(conn); break;*/
            case 9: limpar_tela(); break;
            case 0: std::cout << "Saindo...\n"; break;
            default: limpar_tela(); std::cout << "Opção inválida!\n";
        }
    } while (opcao != 0);
}
