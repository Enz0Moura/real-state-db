#ifndef BASE_TABLE_H
#define BASE_TABLE_H
#include <iostream>
#include <mysql/mysql.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <random>

#define UUID "CHAR(36)"


class BaseTable {
protected:
    std::string tableName;
    std::vector<std::pair<std::string, std::string>> columns;
    std::unordered_map<std::string, std::string> values;
    std::string primaryKey;
    std::vector<std::tuple<std::string, std::string, std::string>> foreignKeys;
public:
    explicit BaseTable(std::string name) : tableName(std::move(name)) {}

    void addColumn(const std::string& columnName, const std::string& columnType);

    void setPrimaryKey(const std::string& column, const std::string& keyType = "");

    void addForeignKey(const std::string& column, const std::string& refTable, const std::string& refColumn, const std::string& onDelete = "");

    void setAttribute(const std::string& columnName, const std::string& value);

    std::string getAttribute(const std::string& columnName) const;

    std::string getCreateQuery() const;

    void createTable(MYSQL* conn);

    std::string getInsertQuery() const;

    bool insert(MYSQL* conn);

    void fetchFromDB(MYSQL* conn);

    static std::string generateUUID();

    static std::string getCurrentDateTime();

    static std::string formatDateTime(std::time_t timestamp, const std::string& fmt="%Y-%m-%d %H:%M:%S");

    static std::time_t stringToTimeT(const std::string& datetime, const std::string& fmt="%Y-%m-%d %H:%M:%S");
};

void createAllTables(MYSQL* conn, const std::vector<BaseTable*>& tables);

#endif //BASE_TABLE_H
