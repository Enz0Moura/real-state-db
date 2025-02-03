#include <mysql/mysql.h>
#include "database/settings.h"
#include "database/tables/BaseTable.h"

class ClienteTable : public BaseTable {
public:
    ClienteTable() : BaseTable("clientes") {
        addColumn("id", "INT AUTO_INCREMENT PRIMARY KEY");
        addColumn("nome", "VARCHAR(255)");
        addColumn("cpf", "VARCHAR(14) UNIQUE");
        addColumn("estado_civil", "VARCHAR(50)");
        addColumn("telefone", "VARCHAR(20)");
    }

    void setNome(const std::string& nome) { setAttribute(1, nome); }
    void setCpf(const std::string& cpf) { setAttribute(2, cpf); }
    void setEstadoCivil(const std::string& estadoCivil) { setAttribute(3, estadoCivil); }
    void setTelefone(const std::string& telefone) { setAttribute(4, telefone); }
};

int main() {
    Database db;
    MYSQL *connection = nullptr;
    try {
        if (!db.test_connection()) {
            db.create(true);
        };
        connection = db.connect();

        ClienteTable client_table;
        client_table.createTable(connection);

        client_table.setNome("John");
        client_table.setCpf("1234");
        client_table.setEstadoCivil("Casado");
        client_table.setTelefone("(22)998490343");
        client_table.insert(connection);


        mysql_close(connection);
    } catch (const std::exception& e){
        std::cerr << "Erro: " << e.what() << std::endl;
        if (connection) mysql_close(connection);
        return -1;
    }
    return 0;
}
