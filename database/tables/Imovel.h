//
// Created by enzo-moura on 2/4/25.
//

#ifndef IMOVEL_H
#define IMOVEL_H
#include "BaseTable.h"


class Imovel: public BaseTable {
    public:
    Imovel() : BaseTable("imoveis") {
        addColumn("id", UUID);
        setPrimaryKey("id", "UUID");
        addColumn("num_comodos", "INTEGER");
        addColumn("num_vagas", "INTEGER");
        addColumn("area_construida", "FLOAT");
    }
    void set_num_comodos(int num_comodos);
    void set_num_vagas(int num_vagas);
    void set_area_construida(float area_construida);

};

Imovel* insert_imovel(MYSQL* conn, int num_comodos, int num_vagas, float area_construida);

#endif //IMOVEL_H
