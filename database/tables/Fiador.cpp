//
// Created by enzo-moura on 2/3/25.
//

#include "Fiador.h"

bool fiador_registered = []() {
    BaseTable::registerTable("fiadores", []() -> std::shared_ptr<BaseTable> {
        return std::make_shared<Fiador>();
    });
    return true;
}();

void Fiador::link_inq_fiador(std::string id_inq){
    setAttribute("id_inq", id_inq);
}

void Fiador::set_cpf(std::string cpf){
    setAttribute("cpf", cpf);
}

void Fiador::set_nome(std::string nome){
    setAttribute("nome", nome);
}

void Fiador::set_saldo(float saldo){
    setAttribute("saldo", std::to_string(saldo));
}

Fiador *insert_fiador(MYSQL *conn, std::string id_inq, std::string cpf, std::string nome, float saldo) {
    auto* fiador = new Fiador();
    fiador->link_inq_fiador(id_inq);
    fiador->set_cpf(cpf);
    fiador->set_nome(nome);
    fiador->set_saldo(saldo);
    fiador->insert(conn);
    return fiador;
}
