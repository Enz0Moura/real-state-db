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

        Inquilino* inquilino = insert_inquilino(connection,"123456", "Kleber", "Maquinista", 100000.32);
        mysql_close(connection);
    } catch (const std::exception& e){
        std::cerr << "Erro: " << e.what() << std::endl;
        if (connection) mysql_close(connection);
        return -1;
    }
    return 0;
}
