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

void TelefoneProprietario::set_id_proprietario(std::string id_proprietario) {
    setAttribute("id_proprietario", id_proprietario);
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

TelefoneProprietario* insert_telefone_proprietario(MYSQL* conn, std::string id_proprietario, std::string numero) {
    auto* telefone_proprietario = new TelefoneProprietario();
    telefone_proprietario->set_numero(numero);
    telefone_proprietario->set_id_proprietario(id_proprietario);
    telefone_proprietario->insert(conn);
    return telefone_proprietario;
}


