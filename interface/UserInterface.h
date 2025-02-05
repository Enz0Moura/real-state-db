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
void listarClientesProposta(MYSQL* conn);
void listarImoveisCadastrados(MYSQL* conn);
void listar_ofertas_por_imovel(MYSQL* conn);
/*
void corretorMaiorRendimento2022(MYSQL* conn);
void listarTresImoveisMaisCaros(MYSQL* conn);
void inserirNovoRegistro(MYSQL* conn);
void atualizarRegistro(MYSQL* conn);
void deletarRegistro(MYSQL* conn);
*/

void menu(MYSQL* conn);
#endif //USERINTERFACE_H
