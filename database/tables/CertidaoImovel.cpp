#include "CertidaoImovel.h"

bool certidao_imovel_registered = []() {
    BaseTable::registerTable("certidoes_imoveis", []() -> std::shared_ptr<BaseTable> {
        return std::make_shared<CertidaoImovel>();
    });
    return true;
}();

void CertidaoImovel::set_id_prop(std::string id_prop) {
    setAttribute("id_prop", id_prop);
}

void CertidaoImovel::set_id_imovel(std::string id_imovel) {
    setAttribute("id_imovel", id_imovel);
}

void CertidaoImovel::set_num_registro(std::string num_registro) {
    setAttribute("num_registro", num_registro);
}

void CertidaoImovel::set_data_registro(std::time_t data_registro) {
    std::string data_registro_str = formatDateTime(data_registro);
    setAttribute("data_registro", data_registro_str);
}

CertidaoImovel *insert_certidao_imovel(MYSQL* conn, std::string id_prop, std::string id_imovel, std::string num_registro, std::optional<std::time_t> data_registro) {
    auto* certidao_imovel = new CertidaoImovel();
    certidao_imovel->set_id_prop(id_prop);
    certidao_imovel->set_id_imovel(id_imovel);
    certidao_imovel->set_num_registro(num_registro);
    if (data_registro != std::nullopt) certidao_imovel->set_data_registro(data_registro.value());
    certidao_imovel->insert(conn);
    return certidao_imovel;
}
