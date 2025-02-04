//
// Created by enzo-moura on 2/4/25.
//

#include "Imovel.h"

void Imovel::set_area_construida(float area_construida) {
    setAttribute("area_construida", std::to_string(area_construida));
}

void Imovel::set_num_comodos(int num_comodos) {
    setAttribute("num_comodos", std::to_string(num_comodos));
}

void Imovel::set_num_vagas(int num_vagas) {
    setAttribute("num_vagas", std::to_string(num_vagas));
}

Imovel* insert_imovel(MYSQL* conn, int num_comodos, int num_vagas, float area_construida) {
    auto* imovel = new Imovel();
    imovel->set_area_construida(area_construida);
    imovel->set_num_comodos(num_comodos);
    imovel->set_num_vagas(num_vagas);
    imovel->insert(conn);
    return imovel;
}

