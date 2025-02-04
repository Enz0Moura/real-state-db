//
// Created by enzo-moura on 2/4/25.
//

#ifndef CORRETORAUTONOMO_H
#define CORRETORAUTONOMO_H
#include "BaseTable.h"


class CorretorAutonomo: public BaseTable {
    public:
    CorretorAutonomo(): BaseTable("corretores_autonomos") {
        addColumn("id", UUID);
        setPrimaryKey("id", "UUID");
        addColumn("creci", std::string(UUID) + " UNIQUE");
        addColumn("nome", "VARCHAR(255)");
        addColumn("data_inicio", "DATETIME");
        addColumn("comissao", "FLOAT");
    };
    void set_creci(std::string creci);
    void set_nome(std::string nome);
    void set_data_inicio(std::string data_inicio);
    void set_comissao(float comissao);
};

CorretorAutonomo* insert_corretor_autonomo(MYSQL* conn, std::string creci, std::string nome, std::string data_inicio, float comissao);


#endif //CORRETORAUTONOMO_H
