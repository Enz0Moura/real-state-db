#include "CorretorAutonomo.h"

bool corretor_autonomo_registered = []() {
    BaseTable::registerTable("corretores_autonomos", []() -> std::shared_ptr<BaseTable> {
        return std::make_shared<CorretorAutonomo>();
    });
    return true;
}();

void CorretorAutonomo::set_creci(std::string creci) {
    setAttribute("creci", creci);
}

void CorretorAutonomo::set_nome(std::string nome) {
    setAttribute("nome", nome);
}

void CorretorAutonomo::set_data_inicio(std::string data_inicio) {
    std::time_t data_timestamp = stringToTimeT(data_inicio, DATE_FORMAT);
    std::string data_date_time = formatDateTime(data_timestamp);
    setAttribute("data_inicio", data_date_time);
}

void CorretorAutonomo::set_comissao(float comissao) {
    setAttribute("comissao", std::to_string(comissao));
}

CorretorAutonomo *insert_corretor_autonomo(MYSQL *conn, std::string creci, std::string nome, std::string data_inicio, float comissao) {
    auto* corretor_autonomo = new CorretorAutonomo();
    corretor_autonomo->set_creci(creci);
    corretor_autonomo->set_nome(nome);
    corretor_autonomo->set_data_inicio(data_inicio);
    corretor_autonomo->set_comissao(comissao);
    corretor_autonomo->insert(conn);
    return corretor_autonomo;
}
