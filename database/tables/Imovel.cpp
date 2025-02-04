//
// Created by enzo-moura on 2/4/25.
//

#include "Imovel.h"

void Imovel::set_cep(std::string cep) {
    setAttribute("cep",cep);
}

void Imovel::set_cidade(std::string cidade) {
    setAttribute("cidade",cidade);
}

void Imovel::set_bairro(std::string bairro) {
    setAttribute("bairro",bairro);
}

void Imovel::set_rua(std::string rua) {
    setAttribute("rua",rua);
}

void Imovel::set_complemento(std::string complemento) {
    setAttribute("complemento",complemento);
}

void Imovel::set_area_construida(float area_construida) {
    setAttribute("area_construida", std::to_string(area_construida));
}

void Imovel::set_num_comodos(int num_comodos) {
    setAttribute("num_comodos", std::to_string(num_comodos));
}

void Imovel::set_num_vagas(int num_vagas) {
    setAttribute("num_vagas", std::to_string(num_vagas));
}

Imovel* insert_imovel(MYSQL* conn, std::string cep, std::string cidade, std::string bairro, std::string rua, std::string complemento, int num_comodos, int num_vagas, float area_construida) {
    auto* imovel = new Imovel();
    imovel->set_cep(cep);
    imovel->set_cidade(cidade);
    imovel->set_bairro(bairro);
    imovel->set_rua(rua);
    imovel->set_complemento(complemento);
    imovel->set_num_comodos(num_comodos);
    imovel->set_num_vagas(num_vagas);
    imovel->set_area_construida(area_construida);
    imovel->insert(conn);
    return imovel;
}

