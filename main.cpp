#include <mysql/mysql.h>
#include "database/settings.h"
#include "database/tables/CertidaoImovel.h"
#include "database/tables/ContratoAluguel.h"
#include "database/tables/CorretorAutonomo.h"
#include "database/tables/Fiador.h"
#include "database/tables/Imovel.h"
#include "database/tables/Inquilino.h"
#include "database/tables/Oferta.h"
#include "database/tables/Proposta.h"
#include "database/tables/Proprietario.h"
#include "database/tables/Telefone.h"
#include "database/tables/Visita.h"

int main() {
    Database db;
    MYSQL *connection = nullptr;
    try {
        db.drop();
        if (!db.test_connection()) {
            db.create(true);
        };
        connection = db.connect();

        Inquilino *inquilino = insert_inquilino(connection, "123456", "Kleber", "Maquinista", 100000.32);
        std::string id_inquilino = inquilino->getAttribute("id");

        Inquilino *inquilino2 = insert_inquilino(connection, "256879", "Joazinho", "Programador", 0.32);
        std::string id_inquilino2 = inquilino2->getAttribute("id");

        Fiador *fiador = insert_fiador(connection, id_inquilino, "15879", "Jao Kleber", 1000.32);
        Fiador *fiador2 = insert_fiador(connection, id_inquilino2, "5502", "Jao do biscoito", 99999.32);
        std::string id_fiador1, id_fiador2;
        id_fiador1 = fiador->getAttribute("id");
        id_fiador2 = fiador2->getAttribute("id");

        TelefoneFiador *telefone_fiador1 = insert_telefone_fiador(connection, id_fiador1, "2358392385");
        TelefoneFiador *telefone_fiador2 = insert_telefone_fiador(connection, id_fiador2, "235844444385");

        TelefoneInquilino *telefone_inquilino = insert_telefone_inquilino(connection, id_inquilino, "382144595");
        TelefoneInquilino *telefone_inquilino2 = insert_telefone_inquilino(connection, id_inquilino2, "3821445555");

        Proprietario *proprietario = insert_proprietario(connection, "123940", "My bro", "Solterasso");

        TelefoneProprietario *telefone_proprietario = insert_telefone_proprietario(
            connection, proprietario->getAttribute("id"), "22348910");
        Imovel *imovel = insert_imovel(connection,"26620040", "Petrópolis", "Centro", "16 de março", "Numero 890", 3, 1, 350.45);

        CertidaoImovel *certidao_imovel = insert_certidao_imovel(connection, proprietario->getAttribute("id"),
                                                                 imovel->getAttribute("id"), BaseTable::generateUUID());

        CorretorAutonomo *corretor_autonomo = insert_corretor_autonomo(connection, BaseTable::generateUUID(), "Kleber",
                                                                       "1987-05-25", 500.221);

        insert_telefone_corretor_autonomo(connection, corretor_autonomo->getAttribute("id"), "(22)482373895");

        Oferta* oferta=insert_oferta(connection, proprietario->getAttribute("id"), imovel->getAttribute("id"), 1230.99, corretor_autonomo->getAttribute("id"));

        insert_visita(connection, inquilino->getAttribute("id"), corretor_autonomo->getAttribute("id"),
                      imovel->getAttribute("id"), "2020-03-13");

        insert_proposta(connection, id_inquilino2, imovel->getAttribute("id"), 1100.99, "2025-05-02");

        insert_contrato_aluguel(connection, id_inquilino2, imovel->getAttribute("id"), BaseTable::generateUUID(), 11000, "2026-06-12");

        std::vector<std::shared_ptr<BaseTable>> inquilinos = BaseTable::fetchAll(connection, "inquilinos");

        for (const auto& record : inquilinos) {
            auto inquilino = std::dynamic_pointer_cast<Inquilino>(record);
            if (inquilino) {
                std::cout << "Inquilino: " << inquilino->getAttribute("nome")
                          << " - CPF: " << inquilino->getAttribute("cpf") << std::endl;
            }
        }


        mysql_close(connection);
    } catch (const std::exception &e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        if (connection) mysql_close(connection);
        return -1;
    }
    return 0;
}

//todo: fazer verificações de integridade dentro do código.
//todo: trocar pk's no DER para UUID
//todo: normalizar nome de métodos e variáveis
//todo: se for deletar oferta, deletará imóvel.