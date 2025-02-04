#include "BaseTable.h"

std::string BaseTable::getCurrentDateTime() {
    std::time_t now = std::time(nullptr);
    return formatDateTime(now);
}

std::string BaseTable::formatDateTime(std::time_t timestamp, const std::string& fmt) {
    std::tm* timeinfo = std::localtime(&timestamp);
    std::ostringstream oss;
    oss << std::put_time(timeinfo, fmt.c_str());
    return oss.str();
}

std::time_t BaseTable::stringToTimeT(const std::string& datetime, const std::string& fmt) {
    std::tm tm = {};
    std::istringstream ss(datetime);

    ss >> std::get_time(&tm, fmt.c_str());

    if (ss.fail()) {
        throw std::runtime_error("Failed converting string to DateTime");
    }

    return std::mktime(&tm);
}

std::string BaseTable::generateUUID() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 15);
    std::uniform_int_distribution<int> dis2(8, 11);

    std::stringstream ss;
    ss << std::hex << std::setfill('0');

    for (int i = 0; i < 8; i++) ss << dis(gen);
    ss << "-";
    for (int i = 0; i < 4; i++) ss << dis(gen);
    ss << "-4"; // UUID v4
    for (int i = 0; i < 3; i++) ss << dis(gen);
    ss << "-";
    ss << dis2(gen); // Primeiro dígito entre 8 e 11
    for (int i = 0; i < 3; i++) ss << dis(gen);
    ss << "-";
    for (int i = 0; i < 12; i++) ss << dis(gen);

    return ss.str();
}

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
        query += "FOREIGN KEY (" + std::get<0>(foreignKeys[i]) + ") REFERENCES " + std::get<1>(foreignKeys[i]);
        if (!std::get<2>(foreignKeys[i]).empty()) {
            query += " ON DELETE " + std::get<2>(foreignKeys[i]);
        }
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
        if (column.second.find("DATETIME") != std::string::npos && values.at(column.first).empty()) {
            const_cast<BaseTable*>(this)->values[column.first] = getCurrentDateTime();
        }

        if (!first) query += ", ";

        query += "'" + values.at(column.first) + "'";
        first = false;
    }

    query += ");";
    return query;
}

bool BaseTable::insert(MYSQL* conn) {
    if (!primaryKey.empty()) {
        auto itUUID = std::find_if(columns.begin(), columns.end(), [&](const auto& col) {
            return col.first == primaryKey && col.second.find("CHAR(36)") != std::string::npos;
        });

        auto itAutoInc = std::find_if(columns.begin(), columns.end(), [&](const auto& col) {
            return col.first == primaryKey && col.second.find("AUTO_INCREMENT") != std::string::npos;
        });

        if (itUUID != columns.end() && values[primaryKey].empty()) {
            values[primaryKey] = generateUUID();
        }

        if (itAutoInc != columns.end()) {
            values.erase(primaryKey);
        }
    }

    std::string query = getInsertQuery();
    if (mysql_query(conn, query.c_str())) {
        throw std::runtime_error("Error inserting into table " + tableName + ": " + std::string(mysql_error(conn)) + "\n");
    }

    if (!primaryKey.empty() && values.find(primaryKey) == values.end()) {
        unsigned long long last_id = mysql_insert_id(conn);
        if (last_id > 0) {
            values[primaryKey] = std::to_string(last_id);
        }
    }

    fetchFromDB(conn);

    std::cout << "Tuple inserted into table " << tableName << " successfully." << std::endl;
    return true;
}


void BaseTable::setPrimaryKey(const std::string& column, const std::string& keyType) {
    primaryKey = column;
    if (keyType == "UUID") {
        for (auto& col : columns) {
            if (col.first == column) {
                col.second = "CHAR(36)";
                return;
            }
        }
        addColumn(column, "CHAR(36)");
    }
}

void BaseTable::addForeignKey(const std::string& column, const std::string& refTable, const std::string& refColumn, const std::string& onDelete){
    foreignKeys.emplace_back(column, refTable + "(" + refColumn + ")", onDelete);
}

void BaseTable::fetchFromDB(MYSQL* conn) {
    if (primaryKey.empty() || values[primaryKey].empty()) {
        throw std::runtime_error("Cannot fetch data without a valid primary key.");
    }
    std::string query_pk = values[primaryKey];

    auto it = std::find_if(columns.begin(), columns.end(), [&](const auto& col) {
        return col.first == primaryKey && col.second.find("CHAR(36)") != std::string::npos;
    });

    if (it->first == "id" && it->second == UUID) {
        query_pk = "'"+query_pk+"'";
    }


    std::string query = "SELECT * FROM " + tableName + " WHERE " + primaryKey + " = " + query_pk + " LIMIT 1;";

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