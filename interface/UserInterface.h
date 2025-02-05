#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <iostream>
#include <vector>
#include <memory>
#include "../database/tables/BaseTable.h"
#include "../database/tables/Inquilino.h"
#include "../database/tables/CorretorAutonomo.h"
#include "../database/tables/Imovel.h"

void limpar_tela();

void listarClientesProposta(MYSQL *conn);

void listarImoveisCadastrados(MYSQL *conn);

void listar_ofertas_por_imovel(MYSQL *conn);

void corretor_maior_rendimento(MYSQL *conn);

void listar_top_tres_imoveis_mais_caros(MYSQL *conn);

void inserir_imovel(MYSQL *conn);

void inserir_novo_registro(MYSQL *conn);

/*void inserirNovoRegistro(MYSQL* conn);
void atualizarRegistro(MYSQL* conn);
void deletarRegistro(MYSQL* conn);
*/

void menu(MYSQL *conn);
#endif //USERINTERFACE_H
