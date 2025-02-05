# Real State DB

##  Visão Geral

O projeto **Real State DB** é um sistema para uma imobiliária, desenvolvido em **Linguagem C++** e utilizando **MySQL** como Sistema Gerenciador de Banco de Dados (SGBD). O objetivo é gerenciar informações de clientes, corretores e imóveis, além de registrar e acompanhar ofertas, visitas e contratos de aluguel.

## 🏗️ Estrutura do Projeto

### 📁 Diretórios e Arquivos

- `src/` - Código-fonte do sistema.
- `database/` - Módulo para criação e manipulação do banco de dados.
- `interface/` - Módulo para interação com usuário.
- `docs/` - Documentação e diagramas.
- `README.md` - Instruções gerais sobre o projeto.
- `main.cpp` - Arquivo principal.

## A estrutura de dados

- **Clientes** (proprietários e inquilinos)

    - Nome, CPF, estado civil, telefones de contato.
    - Registro da posse do imóvel (proprietários).
    - Profissão e renda familiar (inquilinos).
    - Cadastro de fiadores para inquilinos.

- **Corretores**

    - Nome, CRECI, telefone.
    - Data de início na imobiliária.
    - Valor de comissão por negócio fechado.

- **Imóveis**

    - Endereço, número de cômodos, vagas na garagem, área construída.
    - Data da oferta e valor do aluguel.
    - Gerenciamento de ofertas e cancelamentos.

### 📌 Operações do Sistema

- Registrar visitas de inquilinos a imóveis.
- Registrar propostas de aluguel e suas condições (valor, validade).
- Registrar contratos de aluguel com inquilinos e proprietários.
- Gerenciar e atualizar informações do banco de dados.

### 📌 Consultas e Relatórios

- Listagem de clientes cadastrados com propostas realizadas.
- Listagem de imóveis cadastrados (alugados ou não).
- Listagem de ofertas realizadas para um imóvel.
- Identificação do corretor com maior rendimento em um ano específico.
- Listagem dos três imóveis mais caros.
- Outras consultas adicionais relevantes.

## 📚 Biblioteca `Database`

A biblioteca `Database` foi desenvolvida para gerenciar a comunicação entre o sistema e o banco de dados MySQL. Ela possui as seguintes funcionalidades:

### Principais Métodos

- **`load_env(filename)`**: Carrega variáveis de ambiente a partir de um arquivo `.env`.
- **`Database(env_file)`**: Construtor que inicializa a conexão utilizando variáveis de ambiente.
- **`connect()`**: Estabelece uma conexão com o banco de dados.
- **`test_connection()`**: Testa a conexão com o banco de dados e retorna `true` ou `false`.
- **`create(drop_if_exists)`**: Cria o banco de dados e suas tabelas.
- **`create_tables()`**: Cria todas as tabelas definidas no sistema.
- **`drop()`**: Remove o banco de dados.

### Classe BaseTable

A biblioteca utiliza a classe base `BaseTable`, que fornece abstrações para operações comuns em tabelas do banco de dados. Todas as tabelas são derivadas de `BaseTable`, permitindo reuso de código e padronização de operações.

#### 📌 Classe `BaseTable`

A classe `BaseTable` oferece métodos para:

- Definir a estrutura das tabelas (colunas, chaves primárias e estrangeiras).
- Criar tabelas no banco de dados.
- Inserir, atualizar e deletar registros.
- Buscar informações diretamente do banco de dados.
- Gerar UUIDs e manipular datas.

#### 📌 Classes Relacionadas

A biblioteca inclui diversas classes que herdam de `BaseTable` para gerenciar as tabelas do banco:

- `CertidaoImovel`
- `ContratoAluguel`
- `CorretorAutonomo`
- `Fiador`
- `Imovel`
- `Inquilino`
- `Oferta`
- `Proposta`
- `Proprietario`
- `Telefone`
- `Visita`

Essa estrutura modular permite uma melhor organização e manutenção do código.

## Tecnologias Utilizadas

- **Linguagem:** C++
- **Banco de Dados:** MySQL
- **Sistema Operacional Recomendado:** Ubuntu/Linux
- **Bibliotecas:** `libmysqlclient-dev`

## Configuração do Ambiente

### Instalação de Dependências

```sh
sudo apt update && sudo apt install libmysqlclient-dev
```

### 🔗 Conexão com o MySQL

Certifique-se de que o MySQL está instalado e em execução.

Adicione as credenciais do seu usuário no arquivo .env.

### 🏗️ Compilação do Código

Ao compilar o código C++, é necessário linkar as bibliotecas do MySQL:

```sh
g++ -std=c++20 -I/usr/include/mysql -o imobiliaria \
    main.cpp \
    database/settings.cpp \
    database/tables/BaseTable.cpp \
    database/tables/Inquilino.cpp \
    database/tables/Fiador.cpp \
    database/tables/Telefone.cpp \
    database/tables/Proprietario.cpp \
    database/tables/Imovel.cpp \
    database/tables/CertidaoImovel.cpp \
    database/tables/Oferta.cpp \
    database/tables/CorretorAutonomo.cpp \
    database/tables/Visita.cpp \
    database/tables/Proposta.cpp \
    database/tables/ContratoAluguel.cpp \
    interface/UserInterface.cpp \
    database/example.cpp \
    -L/usr/include/mysql -lmysqlclient
```

### 🚀 Execução do Sistema

```sh
./imobiliaria
```