#include "Proposta.h"

void Proposta::set_id_imovel(std::string id_imovel) {
    setAttribute("id_imovel", id_imovel);
}

void Proposta::set_id_inquilino(std::string id_inquilino) {
    setAttribute("id_inquilino", id_inquilino);
}

void Proposta::set_valor(float valor) {
    setAttribute("valor", std::to_string(valor));
}

void Proposta::set_validade(std::string validade) {
    std::string validade_datetime = date_to_datetime(validade);
    setAttribute("validade", validade_datetime);
}

Proposta *insert_proposta(MYSQL* conn, std::string id_inquilino, std::string id_imovel, float valor, std::string validade) {
    auto *proposta = new Proposta();
    proposta->set_id_imovel(id_imovel);
    proposta->set_id_inquilino(id_inquilino);
    proposta->set_valor(valor);
    proposta->set_validade(validade);
    proposta->insert(conn);
    return proposta;
}
