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
        addColumn("cep", "VARCHAR(8)");
        addColumn("cidade", "VARCHAR(100)");
        addColumn("bairro", "VARCHAR(100)");
        addColumn("rua", "VARCHAR(100)");
        addColumn("complemento", "VARCHAR(100)");
        addColumn("num_comodos", "INTEGER");
        addColumn("num_vagas", "INTEGER");
        addColumn("area_construida", "FLOAT");
    }
    void print_imovel();
    void set_cep(std::string cep);
    void set_cidade(std::string cidade);
    void set_bairro(std::string bairro);
    void set_rua(std::string rua);
    void set_complemento(std::string complemento);
    void set_num_comodos(int num_comodos);
    void set_num_vagas(int num_vagas);
    void set_area_construida(float area_construida);

};

Imovel* insert_imovel(MYSQL* conn, std::string cep, std::string cidade, std::string bairro, std::string rua, std::string complemento, int num_comodos, int num_vagas, float area_construida);

#endif //IMOVEL_H
