#ifndef BASE_TABLE_H
#define BASE_TABLE_H
#include <iostream>
#include <mysql/mysql.h>
#include <stdexcept>
#include <string>
#include <vector>
#include <unordered_map>
#include <ctime>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <random>
#include <memory>
#include <functional>

#define UUID "CHAR(36)"
#define DATE_FORMAT "%Y-%m-%d"
#define DATE_TIME_FORMAT "%Y-%m-%d %H:%M:%S"


class BaseTable {
protected:
    std::string tableName;
    std::vector<std::pair<std::string, std::string>> columns;
    std::unordered_map<std::string, std::string> values;
    std::string primaryKey;
    std::vector<std::tuple<std::string, std::string, std::string>> foreignKeys;
public:
    explicit BaseTable(std::string name) : tableName(std::move(name)) {}

    virtual ~BaseTable() = default;

    void set_id(std::string id);

    void addColumn(const std::string& columnName, const std::string& columnType);

    void setPrimaryKey(const std::string& column, const std::string& keyType = "");

    void addForeignKey(const std::string& column, const std::string& refTable, const std::string& refColumn, const std::string& onDelete = "");

    void setAttribute(const std::string& columnName, const std::string& value);

    std::string getAttribute(const std::string& columnName) const;

    std::string getCreateQuery() const;

    void createTable(MYSQL* conn);

    std::string getInsertQuery() const;

    bool insert(MYSQL* conn);

    bool update(MYSQL* conn);

    bool remove_entry(MYSQL* conn);

    void fetchFromDB(MYSQL* conn);

    static std::unordered_map<std::string, std::function<std::shared_ptr<BaseTable>()>> factories;

    static void registerTable(const std::string& tableName, std::function<std::shared_ptr<BaseTable>()> factoryMethod);

    static std::vector<std::shared_ptr<BaseTable>> fetchAll(MYSQL* conn, const std::string& tableName);

    static std::string generateUUID();

    static std::string getCurrentDateTime();

    static std::string formatDateTime(std::time_t timestamp, const std::string& fmt=DATE_TIME_FORMAT);

    static std::time_t stringToTimeT(const std::string& datetime, const std::string& fmt=DATE_TIME_FORMAT);

    static std::string date_to_datetime(const std::string& date, const std::string& fmt=DATE_FORMAT);
};

void createAllTables(MYSQL* conn, const std::vector<BaseTable*>& tables);

#endif //BASE_TABLE_H
