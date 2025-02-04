#ifndef CONTRATOALUGUEL_H
#define CONTRATOALUGUEL_H
#include "BaseTable.h"


class ContratoAluguel: public BaseTable {
    public:
    ContratoAluguel(): BaseTable("contratos_alugueis") {
        addColumn("id", UUID);
        setPrimaryKey("id", "UUID");
        addColumn("id_inquilino", UUID);
        addForeignKey("id_inquilino", "inquilinos", "id", "SET NULL");
        addColumn("id_imovel", UUID);
        addForeignKey("id_imovel", "imoveis", "id", "CASCADE");
        addColumn("num_contrato", std::string(UUID) + " UNIQUE");
        addColumn("valor", "FLOAT");
        addColumn("duracao", "DATETIME");
    }

    void set_id_inquilino(std::string id_inquilino);

    void set_id_imovel(std::string id_imovel);

    void set_num_contrato(std::string num_contrato);

    void set_valor(float valor);

    void set_duracao(std::string duracao);

};

ContratoAluguel* insert_contrato_aluguel(MYSQL* conn, std::string id_inquilino, std::string id_imovel, std::string num_contrato, float valor ,std::string duracao);


#endif //CONTRATOALUGUEL_H
