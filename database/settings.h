#ifndef SETTINGS_H
#define SETTINGS_H

#include <mysql/mysql.h>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <fstream>
#include <iostream>

class Database {
private:
    std::string host;
    std::string username;
    std::string password;
    std::string database;
    unsigned int port;

    std::unordered_map<std::string, std::string> load_env(const std::string& filename);

public:
    explicit Database(const std::string& env_file = "../.env");

    MYSQL* connect();

    bool test_connection();

    int create(bool drop_if_exists = false);

    void create_tables();

    int drop();

};



#endif //SETTINGS_H
