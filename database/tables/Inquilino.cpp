//
// Created by enzo-moura on 2/2/25.
//

#include "Inquilino.h"
#include <sstream>
#include <iomanip>

void Inquilino::set_cpf(std::string cpf) {
    setAttribute(1, cpf);
}
void Inquilino::set_nome(std::string nome){
    setAttribute(2, nome);

}
void Inquilino::set_profissao(std::string profissao){
    setAttribute(3, profissao);
}

void Inquilino::set_renda_familar(float renda_familar) {
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2) << renda_familar;
    setAttribute(4, stream.str());

}