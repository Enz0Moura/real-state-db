#ifndef PROPRIETARIO_H
#define PROPRIETARIO_H
#include "BaseTable.h"


class Proprietario: public BaseTable {
public:
    Proprietario() : BaseTable("proprietarios") {
        addColumn("id", UUID);
        setPrimaryKey("id", "UUID");
        addColumn("cpf", "VARCHAR(14) UNIQUE");
        addColumn("nome", "VARCHAR(255)");
        addColumn("estado_civil", "VARCHAR(50)");
    }
    void set_cpf(std::string cpf);
    void set_nome(std::string nome);
    void set_estado_civil(std::string estado_civil);
};

Proprietario* insert_proprietario(MYSQL* conn, std::string cpf, std::string nome, std::string estado_civil);



#endif //PROPRIETARIO_H
