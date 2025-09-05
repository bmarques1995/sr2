#include <iostream>
#include <unordered_map>
#include <string>
#include <cstdint>
#include "Helper.hpp"
#include "Version.hpp"
#include "Samples.hpp"
#include "AddressLoader.hpp"
#include <sqlite3.h>

const std::unordered_map<std::string, uint32_t> standalone_cmd_option = {
    {"--help", 1},
    {"-h", 1},
    {"--version", 2},
    {"-v", 2},
    {"--test0", 3},
    {"--test1", 4},
    // Add more error codes and messages as needed
};

int main(int argc, char** argv)
{
    sr2::AddressLoader::LoadHTTPAddresses();
    sr2::AddressLoader::LoadTORAddresses();
    sr2::AddressLoader::LoadNOSTRelays();
    
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
                case 3:
                    sr2::CreateSQLiteSampleDB();
                    break;
                case 4:
                    sr2::RequestSampleContent();
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