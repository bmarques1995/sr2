#include "Samples.hpp"
#include <sqlite3.h>
#include <iostream>

void sr2::CreateSQLiteSampleDB()
{
    sqlite3* db;
    sqlite3_stmt* stmt;
    auto db_id = sqlite3_open("sample.sqlite3", &db);
    if (db_id == SQLITE_OK)
    {
        std::cout << "Database opened successfully." << std::endl;
        sqlite3_prepare_v2(db, "CREATE TABLE IF NOT EXISTS sample_table (id INTEGER PRIMARY KEY, name TEXT, age INTEGER);", -1, &stmt, 0);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
        sqlite3_close(db);
    }
}
