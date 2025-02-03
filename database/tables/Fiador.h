//
// Created by enzo-moura on 2/3/25.
//

#ifndef FIADOR_H
#define FIADOR_H
#include "BaseTable.h"


class Fiador: public BaseTable {
public:
    Fiador() : BaseTable("fiadores") {
        addColumn("id", "INT AUTO_INCREMENT");
        setPrimaryKey("id");
        addColumn("id_inq", "INT NOT NULL");
        addForeignKey("id_inq", "inquilinos", "id");
        addColumn("cpf", "VARCHAR(14) UNIQUE");
        addColumn("nome", "VARCHAR(255)");
        addColumn("saldo", "FLOAT");
    }
    void link_inq_fiador(std::string id_inq); // FK deverá ser string para facilitar a consulta
    void set_cpf(std::string cpf);
    void set_nome(std::string nome);
    void set_saldo(float saldo);
};

Fiador* insert_fiador(MYSQL* conn, std::string id_inq, std::string cpf, std::string nome, float saldo);




#endif //FIADOR_H
