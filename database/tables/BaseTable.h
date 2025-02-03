#ifndef BASE_TABLE_H
#define BASE_TABLE_H
#include <mysql/mysql.h>
#include <string>
#include <vector>
#include <iostream>


class BaseTable {
protected:
    std::string tableName;
    std::vector<std::pair<std::string, std::string>> columns;
    std::vector<std::string> columnNames;
    std::vector<std::string> values;
public:
    explicit BaseTable(std::string name) : tableName(std::move(name)) {}

    void addColumn(const std::string& columnName, const std::string& columnType);

    std::string getCreateQuery() const;

    void createTable(MYSQL* conn);

    void setAttribute(size_t index, const std::string& value);

    std::string getInsertQuery() const;

    bool insert(MYSQL* conn);
};

void createAllTables(MYSQL* conn, const std::vector<BaseTable*>& tables);

#endif //BASE_TABLE_H
