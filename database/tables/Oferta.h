#ifndef OFERTA_H
#define OFERTA_H
#include "BaseTable.h"
#include <optional>


class Oferta: public BaseTable {
    public:
    Oferta(): BaseTable("ofertas") {
        addColumn("id", UUID);
        setPrimaryKey("id", "UUID");
        addColumn("id_prop", std::string(UUID) + " NOT NULL");
        addForeignKey("id_prop", "proprietarios", "id", "CASCADE");
        addColumn("id_imovel", std::string(UUID) + " NOT NULL");
        addForeignKey("id_imovel", "imoveis", "id", "CASCADE");
        addColumn("id_corretor", std::string(UUID) + " NULL");
        addForeignKey("id_corretor", "corretores_autonomos", "id", "SET NULL");
        setAttribute("id_corretor", "NULL");
        addColumn("valor_desejado", "FLOAT");
        addColumn("data", "DATETIME");
    }
    void set_id_prop(std::string id_prop);
    void set_id_imovel(std::string id_imovel);
    void set_id_corretor(std::string id_corretor);
    void set_data(std::string data);
    void set_valor_desejado(float valor_desejado);
};

Oferta* insert_oferta(MYSQL* conn, std::string id_prop, std::string id_imovel, float valor_desejado, std::optional<std::string> id_corretor=std::nullopt, std::optional<std::string> data=std::nullopt);

#endif //OFERTA_H
