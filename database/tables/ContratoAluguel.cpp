#include "ContratoAluguel.h"

bool contrato_aluguel_registered = []() {
    BaseTable::registerTable("contratos_alugueis", []() -> std::shared_ptr<BaseTable> {
        return std::make_shared<ContratoAluguel>();
    });
    return true;
}();


void ContratoAluguel::set_id_inquilino(std::string id_inquilino) {
    setAttribute("id_inquilino", id_inquilino);
}

void ContratoAluguel::set_id_imovel(std::string id_imovel) {
    setAttribute("id_imovel", id_imovel);
}


void ContratoAluguel::set_num_contrato(std::string num_contrato) {
    setAttribute("num_contrato", num_contrato);
}

void ContratoAluguel::set_valor(float valor) {
    setAttribute("valor", std::to_string(valor));
}

void ContratoAluguel::set_duracao(std::string duracao) {
    std::string duracao_datetime = date_to_datetime(duracao);
    setAttribute("duracao", duracao_datetime);
}

ContratoAluguel *insert_contrato_aluguel(MYSQL *conn, std::string id_inquilino, std::string id_imovel, std::string num_contrato, float valor, std::string duracao) {
    auto* contrato_aluguel = new ContratoAluguel();
    contrato_aluguel->set_id_inquilino(id_inquilino);
    contrato_aluguel->set_id_imovel(id_imovel);
    contrato_aluguel->set_num_contrato(num_contrato);
    contrato_aluguel->set_valor(valor);
    contrato_aluguel->set_duracao(duracao);
    contrato_aluguel->insert(conn);
    return contrato_aluguel;
}
