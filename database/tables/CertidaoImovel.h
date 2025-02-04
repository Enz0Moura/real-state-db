//
// Created by enzo-moura on 2/4/25.
//

#ifndef CERTIDAOIMOVEL_H
#define CERTIDAOIMOVEL_H
#include <optional>

#include "BaseTable.h"


class CertidaoImovel: public BaseTable {
    public:
    CertidaoImovel(): BaseTable("certidoes_imoveis") {
        addColumn("id", UUID);
        setPrimaryKey("id", "UUID");
        addColumn("id_prop", std::string(UUID) + " NOT NULL");
        addForeignKey("id_prop", "proprietarios", "id", "CASCADE");
        addColumn("id_imovel", std::string(UUID) + " NOT NULL");
        addForeignKey("id_imovel", "imoveis", "id", "CASCADE");
        addColumn("data_registro", "DATETIME");
    }

    void set_id_prop(std::string id_prop);
    void set_id_imovel(std::string id_imovel);
    void set_data_registro(std::time_t data_registro);

};

CertidaoImovel* insert_certidao_imovel(MYSQL* conn, std::string id_prop, std::string id_imovel, std::optional<std::time_t> data_registro= std::nullopt);



#endif //CERTIDAOIMOVEL_H
