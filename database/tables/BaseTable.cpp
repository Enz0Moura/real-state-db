#include "BaseTable.h"

void BaseTable::addColumn(const std::string& columnName, const std::string& columnType) {
    columns.emplace_back(columnName, columnType);
    values[columnName] = "";
}

std::string BaseTable::getCreateQuery() const {
    std::string query = "CREATE TABLE IF NOT EXISTS " + tableName + " (";
    for (size_t i = 0; i < columns.size(); ++i) {
        query += columns[i].first + " " + columns[i].second;
        if (i < columns.size() - 1 || !primaryKey.empty() || !foreignKeys.empty()) {
            query += ", ";
        }
    }

    if (!primaryKey.empty()) {
        query += "PRIMARY KEY (" + primaryKey + ")";
        if (!foreignKeys.empty()) query += ", ";
    }

    for (size_t i = 0; i < foreignKeys.size(); ++i) {
        query += "FOREIGN KEY (" + foreignKeys[i].first + ") REFERENCES " + foreignKeys[i].second;
        if (i < foreignKeys.size() - 1) {
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

void BaseTable::setAttribute(const std::string& columnName, const std::string& value) {
    if (values.find(columnName) != values.end()) {
        values[columnName] = value;
    } else {
        throw std::invalid_argument("Column '" + columnName + "' does not exist in table " + tableName);
    }
}

std::string BaseTable::getAttribute(const std::string& columnName) const {
    auto it = values.find(columnName);
    if (it != values.end()) {
        return it->second;
    }
    throw std::invalid_argument("Column '" + columnName + "' does not exist in table " + tableName);
}


std::string BaseTable::getInsertQuery() const {
    std::string query = "INSERT INTO " + tableName + " (";

    bool first = true;
    for (const auto& column : columns) {
        if (column.first == primaryKey && column.second.find("AUTO_INCREMENT") != std::string::npos) {
            continue;
        }
        if (!first) query += ", ";
        query += column.first;
        first = false;
    }

    query += ") VALUES (";
    first = true;

    for (const auto& column : columns) {
        if (column.first == primaryKey && column.second.find("AUTO_INCREMENT") != std::string::npos) {
            continue;
        }
        if (!first) query += ", ";
        query += "'" + values.at(column.first) + "'";
        first = false;
    }

    query += ");";
    return query;
}

bool BaseTable::insert(MYSQL* conn) {
    std::string query = getInsertQuery();
    if (mysql_query(conn, query.c_str())) {
        throw std::runtime_error("Error inserting into table " + tableName + ": " + std::string(mysql_error(conn)) + "\n");
    }

    if (!primaryKey.empty() && values.find(primaryKey) != values.end()) {
        unsigned long long last_id = mysql_insert_id(conn);
        if (last_id > 0) {
            values[primaryKey] = std::to_string(last_id);
        }
    }

    fetchFromDB(conn);

    std::cout << "Tuple inserted into table " << tableName << " successfully." << std::endl;
    return true;
}

void BaseTable::setPrimaryKey(const std::string& column) {
    primaryKey = column;
}

void BaseTable::addForeignKey(const std::string &column, const std::string &refTable, const std::string &refColumn) {
    foreignKeys.emplace_back(column, refTable + "(" + refColumn + ")");
}

void BaseTable::fetchFromDB(MYSQL* conn) {
    if (primaryKey.empty() || values[primaryKey].empty()) {
        throw std::runtime_error("Cannot fetch data without a valid primary key.");
    }

    std::string query = "SELECT * FROM " + tableName + " WHERE " + primaryKey + " = " + values[primaryKey] + " LIMIT 1;";

    if (mysql_query(conn, query.c_str())) {
        throw std::runtime_error("Error fetching data from table " + tableName + ": " + std::string(mysql_error(conn)) + "\n");
    }

    MYSQL_RES* res = mysql_store_result(conn);
    if (!res) {
        throw std::runtime_error("Error retrieving result set: " + std::string(mysql_error(conn)) + "\n");
    }

    MYSQL_ROW row = mysql_fetch_row(res);
    if (row) {
        unsigned int num_fields = mysql_num_fields(res);
        MYSQL_FIELD* fields = mysql_fetch_fields(res);
        for (unsigned int i = 0; i < num_fields; i++) {
            values[fields[i].name] = row[i] ? row[i] : "";
        }
    }

    mysql_free_result(res);
};