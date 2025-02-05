#include "Visita.h"

bool visita_registered = []() {
    BaseTable::registerTable("visitas", []() -> std::shared_ptr<BaseTable> {
        return std::make_shared<Visita>();
    });
    return true;
}();

void Visita::set_id_corretor(std::string &id_corretor) {
    setAttribute("id_corretor", id_corretor);
}

void Visita::set_id_imovel(std::string &id_imovel) {
    setAttribute("id_imovel", id_imovel);
}

void Visita::set_id_inquilino(std::string &id_inquilino) {
    setAttribute("id_inquilino", id_inquilino);
}

void Visita::set_data(std::string& data) {
    std::string data_date_time = date_to_datetime(data);
    setAttribute("data", data_date_time);
}

Visita *insert_visita(MYSQL *conn, std::string id_inquilino, std::string id_corretor, std::string id_imovel, std::string data) {
    auto* visita = new Visita();
    visita->set_id_corretor(id_corretor);
    visita->set_id_imovel(id_imovel);
    visita->set_id_inquilino(id_inquilino);
    visita->set_data(data);
    visita->insert(conn);
    return visita;
}

