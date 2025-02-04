#ifndef PROPOSTA_H
#define PROPOSTA_H
#include "BaseTable.h"


class Proposta: public BaseTable {
    public:
    Proposta(): BaseTable("propostas") {
        addColumn("id", UUID);
        setPrimaryKey("id", "UUID");
        addColumn("id_inquilino", UUID);
        addForeignKey("id_inquilino", "inquilinos", "id", "SET NULL");
        addColumn("id_imovel", UUID);
        addForeignKey("id_imovel", "imoveis", "id", "CASCADE");
        addColumn("valor", "FLOAT");
        addColumn("validade", "DATETIME");
    };

    void set_id_inquilino(std::string id_inquilino);
    void set_id_imovel(std::string id_imovel);
    void set_valor(float valor);
    void set_validade(std::string validade);
};

Proposta* insert_proposta(MYSQL* conn, std::string id_inquilino, std::string id_imovel, float valor, std::string validade);


#endif //PROPOSTA_H
