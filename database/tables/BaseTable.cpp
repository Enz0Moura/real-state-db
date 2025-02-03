#include "BaseTable.h"

void BaseTable::addColumn(const std::string& columnName, const std::string& columnType) {
    columns.emplace_back(columnName, columnType);
    columnNames.push_back(columnName);
    values.push_back("");
}

std::string BaseTable::getCreateQuery() const {
    std::string query = "CREATE TABLE IF NOT EXISTS " + tableName + " (";
    for (size_t i = 0; i < columns.size(); ++i) {
        query += columns[i].first + " " + columns[i].second;
        if (i < columns.size() - 1) {
            query += ", ";
        }
    }
    query += ");";
    return query;
}

void BaseTable::createTable(MYSQL* conn) {
    std::string query = getCreateQuery();
    if (mysql_query(conn, query.c_str())) {
        throw std::runtime_error("Error creating table " + tableName + ": " + std::string(mysql_error(conn)) + "\n");
    }
    std::cout << "Table " << tableName << " successfully created." << std::endl;
}

void createAllTables(MYSQL* conn, const std::vector<BaseTable*>& tables) {
    for (const auto& table : tables) {
        table->createTable(conn);
    }
}

void BaseTable::setAttribute(size_t index, const std::string& value) {
    if (index > 0 && index < values.size()) {
        values[index] = value;
    }
}

std::string BaseTable::getInsertQuery() const {
    std::string query = "INSERT INTO " + tableName + " (";

    for (size_t i = 1; i < columnNames.size(); ++i) {
        query += columnNames[i];
        if (i < columnNames.size() - 1) {
            query += ", ";
        }
    }
    query += ") VALUES (";

    for (size_t i = 1; i < values.size(); ++i) {
        query += "'" + values[i] + "'";
        if (i < values.size() - 1) {
            query += ", ";
        }
    }
    query += ");";

    return query;
}

bool BaseTable::insert(MYSQL* conn) {
    std::string query = getInsertQuery();
    if (mysql_query(conn, query.c_str())) {
        throw std::runtime_error("Error inserting on table " + tableName + ": " + std::string(mysql_error(conn)) + "\n");
    }

    std::cout << "Tuple inserted on table " << tableName << " successfully." << std::endl;
    return true;
}