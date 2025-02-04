#include "Oferta.h"

void Oferta::set_data(std::string data) {
    std::time_t data_timestamp = stringToTimeT(data, DATE_FORMAT);
    std::string data_date_time = formatDateTime(data_timestamp);
    setAttribute("data", data_date_time);
}

void Oferta::set_id_imovel(std::string id_imovel) {
    setAttribute("id_imovel", id_imovel);
}

void Oferta::set_id_prop(std::string id_prop) {
    setAttribute("id_prop", id_prop);
}

void Oferta::set_valor_desejado(float valor_desejado) {
    setAttribute("valor_desejado", std::to_string(valor_desejado));
}


Oferta *insert_oferta(MYSQL *conn, std::string id_prop, std::string id_imovel, float valor_desejado, std::optional<std::string> data) {
    auto* oferta = new Oferta();
    oferta->set_id_prop(id_prop);
    oferta->set_id_imovel(id_imovel);
    if (data != std::nullopt) oferta->set_data(data.value());
    oferta->set_valor_desejado(valor_desejado);
    oferta->insert(conn);
    return oferta;
}
