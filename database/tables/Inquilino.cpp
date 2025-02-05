#include "Inquilino.h"
#include <sstream>
#include <iomanip>

bool inquilino_registered = []() {
    BaseTable::registerTable("inquilinos", []() -> std::shared_ptr<BaseTable> {
        return std::make_shared<Inquilino>();
    });
    return true;
}();

void Inquilino::set_cpf(std::string cpf) {
    setAttribute("cpf", cpf);
}
void Inquilino::set_nome(std::string nome){
    setAttribute("nome", nome);

}
void Inquilino::set_profissao(std::string profissao){
    setAttribute("profissao", profissao);
}

void Inquilino::set_renda_familar(float renda_familar) {
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2) << renda_familar;
    setAttribute("renda_familiar", stream.str());

};

Inquilino* insert_inquilino(MYSQL* conn, std::string cpf, std::string nome, std::string profissao, float renda_familar){
    auto* inquilino = new Inquilino();
    inquilino->set_nome(nome);
    inquilino->set_cpf(cpf);
    inquilino->set_profissao(profissao);
    inquilino->set_renda_familar(renda_familar);
    inquilino->insert(conn);
    return inquilino;
};
