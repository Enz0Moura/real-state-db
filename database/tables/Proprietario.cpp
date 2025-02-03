//
// Created by enzo-moura on 2/3/25.
//

#include "Proprietario.h"

void Proprietario::set_cpf(std::string cpf) {
    setAttribute("cpf", cpf);
}

void Proprietario::set_nome(std::string nome) {
    setAttribute("nome", nome);
}

void Proprietario::set_estado_civil(std::string estado_civil) {
    setAttribute("estado_civil", estado_civil);
}

Proprietario *insert_proprietario(MYSQL *conn, std::string cpf, std::string nome, std::string estado_civil) {
    auto* proprietario = new Proprietario();
    proprietario->set_cpf(cpf);
    proprietario->set_nome(nome);
    proprietario->set_estado_civil(estado_civil);
    proprietario->insert(conn);
    return proprietario;
}


