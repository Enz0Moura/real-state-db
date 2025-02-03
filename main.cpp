#include <mysql/mysql.h>
#include "database/settings.h"
#include "database/tables/Fiador.h"
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

        Inquilino* inquilino = insert_inquilino(connection,"123456", "Kleber", "Maquinista", 100000.32);
        std::string id_inquilino = inquilino->getAttribute("id");

        Inquilino* inquilino2 = insert_inquilino(connection,"256879", "Joazinho", "Programador", 0.32);
        std::string id_inquilino2 = inquilino2->getAttribute("id");

        Fiador* fiador2 = insert_fiador(connection, id_inquilino2, "5502", "Jao do biscoito", 99999.32);
        Fiador* fiador = insert_fiador(connection, id_inquilino, "15879", "Jao Kleber", 1000.32);


        mysql_close(connection);
    } catch (const std::exception& e){
        std::cerr << "Erro: " << e.what() << std::endl;
        if (connection) mysql_close(connection);
        return -1;
    }
    return 0;
}
