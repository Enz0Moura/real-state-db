//
// Created by enzo-moura on 2/2/25.
//

#ifndef INQUILINO_H
#define INQUILINO_H
#include "BaseTable.h"


class Inquilino: public BaseTable {
public:
    Inquilino() : BaseTable("inquilinos") {
        addColumn("id", UUID);
        setPrimaryKey("id", "UUID");
        addColumn("cpf", "VARCHAR(14) UNIQUE");
        addColumn("nome", "VARCHAR(255)");
        addColumn("profissao", "VARCHAR(50)");
        addColumn("renda_familiar", "FLOAT");
    }
    void set_cpf(std::string cpf);
    void set_nome(std::string nome);
    void set_profissao(std::string profissao);
    void set_renda_familar(float renda_familar);
};

Inquilino* insert_inquilino(MYSQL* conn, std::string cpf, std::string nome, std::string profissao, float renda_familar);

#endif //INQUILINO_H
