#include "Oferta.h"

bool oferta_registered = []() {
    BaseTable::registerTable("ofertas", []() -> std::shared_ptr<BaseTable> {
        return std::make_shared<Oferta>();
    });
    return true;
}();


void Oferta::set_data(std::string data) {
    std::string data_date_time = date_to_datetime(data);
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

void Oferta::set_id_corretor(std::string id_corretor) {
    setAttribute("id_corretor", id_corretor);
}


Oferta *insert_oferta(MYSQL *conn, std::string id_prop, std::string id_imovel, float valor_desejado, std::optional<std::string> id_corretor, std::optional<std::string> data) {
    auto* oferta = new Oferta();
    oferta->set_id_prop(id_prop);
    oferta->set_id_imovel(id_imovel);
    if (data != std::nullopt) oferta->set_data(data.value());
    if (id_corretor != std::nullopt) oferta->set_id_corretor(id_corretor.value());
    oferta->set_valor_desejado(valor_desejado);
    oferta->insert(conn);
    return oferta;
}
