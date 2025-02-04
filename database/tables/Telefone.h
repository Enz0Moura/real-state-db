//
// Created by enzo-moura on 2/3/25.
//

#ifndef TELEFONE_H
#define TELEFONE_H
#include "BaseTable.h"


class Telefone: public BaseTable {
public:
    explicit Telefone(const std::string& nome_tabela) : BaseTable(nome_tabela) {
        addColumn("id", UUID);
        setPrimaryKey("id", "UUID");
        addColumn("numero", "VARCHAR(30) UNIQUE");
    }
    void set_numero(std::string numero);
};

class TelefoneInquilino: public Telefone {
public:
    TelefoneInquilino() : Telefone("telefones_inquilinos") {
        addColumn("id_inquilino", std::string(UUID) + " NOT NULL");
        addForeignKey("id_inquilino", "inquilinos", "id", "CASCADE");
    }
    void set_id_inquilino(std::string id_inquilino);
};

class TelefoneFiador: public Telefone {
public:
    TelefoneFiador() : Telefone("telefones_fiadores") {
        addColumn("id_fiador", std::string(UUID) + "NOT NULL");
        addForeignKey("id_fiador", "fiadores", "id", "CASCADE");
    }
    void set_id_fiador(std::string id_fiador);
};

class TelefoneProprietario: public Telefone {
public:
    TelefoneProprietario() : Telefone("telefones_proprietarios") {
        addColumn("id_proprietario", std::string(UUID) + "NOT NULL");
        addForeignKey("id_proprietario", "proprietarios", "id", "CASCADE");
    }
    void set_id_proprietario(std::string id_proprietario);
};

class TelefoneCorretorAutonomo: public Telefone {
public:
    TelefoneCorretorAutonomo() : Telefone("telefones_corretores_autonomos") {
        addColumn("id_corretor", std::string(UUID) + "NOT NULL");
        addForeignKey("id_corretor", "corretores_autonomos", "id", "CASCADE");
    }
    void set_id_corretor_autonomo(std::string id_corretor);
};

TelefoneInquilino* insert_telefone_inquilino(MYSQL* conn, std::string id_inquilino, std::string numero);

TelefoneFiador* insert_telefone_fiador(MYSQL* conn, std::string id_fiador, std::string numero);

TelefoneProprietario* insert_telefone_proprietario(MYSQL* conn, std::string id_proprietario, std::string numero);

TelefoneCorretorAutonomo* insert_telefone_corretor_autonomo(MYSQL* conn, std::string id_corretor, std::string numero);

#endif //TELEFONE_H
