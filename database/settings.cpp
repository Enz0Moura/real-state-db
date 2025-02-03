#include "settings.h"
#include "stdexcept"
#include "tables/Fiador.h"
#include "tables/Inquilino.h"
#include "tables/Proprietario.h"
#include "tables/Telefone.h"

std::unordered_map<std::string, std::string> Database::load_env(const std::string& filename) {
    std::unordered_map<std::string, std::string> env_vars;
    std::ifstream file(filename);

    if (!file) {
        std::cerr << "No .env found " << filename << std::endl;
        return env_vars;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key, value;

        if (std::getline(iss, key, '=') && std::getline(iss, value)) {
            env_vars[key] = value;
        }
    }

    file.close();
    return env_vars;
}

Database::Database(const std::string& env_file ) {
    std::unordered_map<std::string, std::string>  env = load_env(env_file);

    host = env["DB_HOST"];
    username = env["DB_USER"];
    password = env["DB_PASSWORD"];
    database = env["DB_NAME"];
    port = std::stoi(env["DB_PORT"]);
}

MYSQL* Database::connect() {
    MYSQL* conn = mysql_init(nullptr);

    if (!conn) {
        throw std::runtime_error("MySQL initialization failed!\n");
    }

    conn = mysql_real_connect(conn, host.c_str(), username.c_str(), password.c_str(),
                              database.c_str(), port, nullptr, 0);
    if (!conn) {
        throw std::runtime_error("Failed to connect to Database: " + std::string(mysql_error(conn)) + "\n") ;
    }

    std::cout << "Connected to database successfully!" << std::endl;
    return conn;
}

bool Database::test_connection() {
    MYSQL* conn = mysql_init(nullptr);

    if (!conn) {
    throw std::runtime_error("MySQL initialization failed!\n");
    }
    conn = mysql_real_connect(conn, host.c_str(), username.c_str(), password.c_str(),
                              database.c_str(), port, nullptr, 0);
    if (!conn) {
        std::cout << "Couldn't connect to Database: " + std::string(mysql_error(conn)) + "\n" ;
        return false;
    }
    std::cout << "Could connect to database successfully!" << std::endl;
    return true;
}

int Database::create(bool drop_if_exists) {
    std::stringstream ss;

    if (drop_if_exists) {
        if (this->test_connection()) this->drop();
    }

    MYSQL *conn = mysql_init(0);
    conn = mysql_real_connect(conn, host.c_str(), username.c_str(), password.c_str(),
                              nullptr, port, nullptr, 0);

    if (!conn) {
        throw std::runtime_error("Failed to connect to MySQL: " + std::string(mysql_error(conn)) + "\n") ;
    };

    ss << "CREATE DATABASE IF NOT EXISTS " + std::string(database) + ";";
    std::string query = ss.str();

    if (mysql_query(conn, query.c_str())) {
        const char* error = mysql_error(conn);
        mysql_close(conn);
        throw std::runtime_error("Failed to create database: " + std::string(error) + "\n");
    }

    std::cout << "Database " + std::string(database) + " created!" << std::endl;
    mysql_close(conn);
    this->create_tables();
    return 0;
}

void Database::create_tables() {
    MYSQL *conn = mysql_init(0);
    conn = mysql_real_connect(conn, host.c_str(), username.c_str(), password.c_str(),
                              database.c_str(), port, nullptr, 0);

    if (!conn) {
        throw std::runtime_error("Failed to connect to MySQL: " + std::string(mysql_error(conn)) + "\n") ;
    };

    Inquilino inquilino;
    Fiador fiador;
    Proprietario proprietario;
    TelefoneFiador telefone_fiador;
    TelefoneInquilino telefone_inquilino;
    TelefoneProprietario telefone_proprietario;

    std::vector<BaseTable*> tables = {&inquilino, &fiador, &proprietario, &telefone_fiador, &telefone_inquilino, &telefone_proprietario};
    createAllTables(conn, tables);
}


int Database::drop() {
    std::stringstream ss;

    MYSQL *conn = mysql_init(0);
    conn = mysql_real_connect(conn, host.c_str(), username.c_str(), password.c_str(),
                              database.c_str(), port, nullptr, 0);

    if (!conn) {
        throw std::runtime_error("Failed to connect to MySQL: " + std::string(mysql_error(conn)) + "\n") ;
    };

    ss << "DROP DATABASE IF EXISTS " + std::string(database) + ";";
    std::string query = ss.str();

    if (mysql_query(conn, query.c_str())) {
        const char* error = mysql_error(conn);
        mysql_close(conn);
        throw std::runtime_error("Failed to drop database: " + std::string(error) + "\n");
    }

    std::cout << "Database " + std::string(database) + " dropped!" << std::endl;
    mysql_close(conn);
    return 0;
}