//
// Created by enzo-moura on 2/4/25.
//

#ifndef OFERTA_H
#define OFERTA_H
#include <optional>

#include "BaseTable.h"


class Oferta: public BaseTable {
    public:
    Oferta(): BaseTable("ofertas") {
        addColumn("id", UUID);
        setPrimaryKey("id", "UUID");
        addColumn("id_prop", std::string(UUID) + " NOT NULL");
        addForeignKey("id_prop", "proprietarios", "id", "CASCADE");
        addColumn("id_imovel", std::string(UUID) + " NOT NULL");
        addForeignKey("id_imovel", "imoveis", "id", "CASCADE");
        addColumn("data", "DATETIME");
        addColumn("valor_desejado", "FLOAT");
    }
    void set_id_prop(std::string id_prop);
    void set_id_imovel(std::string id_imovel);
    void set_data(std::string data);
    void set_valor_desejado(float valor_desejado);
};

Oferta* insert_oferta(MYSQL* conn, std::string id_prop, std::string id_imovel, float valor_desejado, std::optional<std::string> data=std::nullopt);

#endif //OFERTA_H
