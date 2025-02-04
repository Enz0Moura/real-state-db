//
// Created by enzo-moura on 2/4/25.
//

#ifndef VISITA_H
#define VISITA_H
#include "BaseTable.h"


class Visita: public BaseTable {
    public:
    Visita(): BaseTable("visitas") {
        addColumn("id", UUID);
        setPrimaryKey("id", "UUID");
        addColumn("id_inquilino", UUID);
        addForeignKey("id_inquilino", "inquilinos", "id", "SET NULL");
        addColumn("id_imovel", UUID);
        addForeignKey("id_imovel", "imoveis", "id", "CASCADE");
        addColumn("id_corretor", UUID);
        addForeignKey("id_corretor", "corretores_autonomos", "id", "SET NULL");
        addColumn("data", "DATETIME");
    };
    void set_id_inquilino(std::string& id_inquilino);
    void set_id_corretor(std::string& id_corretor);
    void set_id_imovel(std::string& id_imovel);
    void set_data(std::string& data);
};

Visita* insert_visita(MYSQL* conn, std::string id_inquilino, std::string id_corretor, std::string id_imovel, std::string data);



#endif //VISITA_H
