//
// Created by enzo-moura on 2/3/25.
//

#include "Telefone.h"

void Telefone::set_numero(std::string numero) {
    setAttribute("numero", numero);
}

void TelefoneInquilino::set_id_inquilino(std::string id_inquilino) {
    setAttribute("id_inquilino", id_inquilino);
}

void TelefoneFiador::set_id_fiador(std::string id_fiador) {
    setAttribute("id_fiador", id_fiador);
}

TelefoneInquilino* insert_telefone_inquilino(MYSQL* conn, std::string id_inquilino, std::string numero){
    auto* telefone_inquilino = new TelefoneInquilino();
    telefone_inquilino->set_numero(numero);
    telefone_inquilino->set_id_inquilino(id_inquilino);
    telefone_inquilino->insert(conn);
    return telefone_inquilino;
}

TelefoneFiador* insert_telefone_fiador(MYSQL* conn, std::string id_fiador, std::string numero){
    auto* telefone_fiador = new TelefoneFiador();
    telefone_fiador->set_numero(numero);
    telefone_fiador->set_id_fiador(id_fiador);
    telefone_fiador->insert(conn);
    return telefone_fiador;

}


