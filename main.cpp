#include <mysql/mysql.h>
#include "database/settings.h"
#include "database/example.h"
#include "interface/UserInterface.h"

int main() {
    Database db;
    MYSQL *connection = nullptr;
    try {
        db.drop();
        if (!db.test_connection()) {
            db.create(true);
        };
        connection = db.connect();
        example();
        menu(connection);

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

// Como compilar
/* g++ -std=c++20 -I/usr/include/mysql -o imobiliaria_BD \
    main.cpp \
    database/settings.cpp \
    database/tables/BaseTable.cpp \
    database/tables/Inquilino.cpp \
    database/tables/Fiador.cpp \
    database/tables/Telefone.cpp \
    database/tables/Proprietario.cpp \
    database/tables/Imovel.cpp \
    database/tables/CertidaoImovel.cpp \
    database/tables/Oferta.cpp \
    database/tables/CorretorAutonomo.cpp \
    database/tables/Visita.cpp \
    database/tables/Proposta.cpp \
    database/tables/ContratoAluguel.cpp \
    interface/UserInterface.cpp \
    database/example.cpp \
    -L/usr/include/mysql -lmysqlclient
*/