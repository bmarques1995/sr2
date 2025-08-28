#include <iostream>
#include <unordered_map>
#include <string>
#include <cstdint>
#include "Helper.hpp"
#include "Version.hpp"
#include <sqlite3.h>

const std::unordered_map<std::string, uint32_t> standalone_cmd_option = {
    {"--help", 1},
    {"-h", 1},
    {"--version", 2},
    {"-v", 2},
    // Add more error codes and messages as needed
};

int main(int argc, char** argv)
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
    for (size_t i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        auto it = standalone_cmd_option.find(arg);
        if (it != standalone_cmd_option.end()) {
            switch (it->second) {
                case 1:
                    sr2::DisplayHelp();
                    break;
                case 2:
                    sr2::DisplayVersion();
                    break;
                default:
                    std::cerr << "Unknown option: " << arg << "\n";
                    break;
            }
        } else {
            std::cerr << "Unknown option: " << arg << "\n";
        }
    }
    return 0;
}