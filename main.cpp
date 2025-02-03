#include <mysql/mysql.h>
#include "database/settings.h"
#include "database/tables/Inquilino.h"

int main() {
    Database db;
    MYSQL *connection = nullptr;
    try {
        db.drop();
        if (!db.test_connection()) {
            db.create(true);
        };
        connection = db.connect();

        Inquilino inquilino;
        std::vector<BaseTable*> tables = {&(inquilino)};

        createAllTables(connection, tables);

        inquilino.set_nome("John");
        inquilino.set_cpf("1234");
        inquilino.set_profissao("Programador");
        inquilino.set_renda_familar(10000.3234);
        inquilino.insert(connection);


        mysql_close(connection);
    } catch (const std::exception& e){
        std::cerr << "Erro: " << e.what() << std::endl;
        if (connection) mysql_close(connection);
        return -1;
    }
    return 0;
}
