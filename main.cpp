#include <mysql/mysql.h>
#include "database/settings.h"
#include "database/tables/Fiador.h"
#include "database/tables/Inquilino.h"
#include "database/tables/Telefone.h"

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
        std::string id_fiador1, id_fiador2;
        id_fiador1 = fiador->getAttribute("id");
        id_fiador2 = fiador2->getAttribute("id");

        TelefoneFiador* telefone_fiador1 = insert_telefone_fiador(connection, id_fiador1, "2358392385");
        TelefoneFiador* telefone_fiador2 = insert_telefone_fiador(connection, id_fiador2, "235844444385");

        TelefoneInquilino* telefone_inquilino = insert_telefone_inquilino(connection, id_inquilino, "382144595");
        TelefoneInquilino* telefone_inquilino2 = insert_telefone_inquilino(connection, id_inquilino2, "3821445555");


        mysql_close(connection);
    } catch (const std::exception& e){
        std::cerr << "Erro: " << e.what() << std::endl;
        if (connection) mysql_close(connection);
        return -1;
    }
    return 0;
}


//todo: reminder NÃO UTILIZAR CASCADE EM TODAS AS ENTIDADES
