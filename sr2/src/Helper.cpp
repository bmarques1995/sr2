#include "Helper.hpp"
#include <iostream>

void sr2::DisplayHelp()
{
    std::cout << "Usage: sr2 [options]\n\n"
              << "Options:\n"
              << "  --help, -h        Show this help message\n"
              << "  --version, -v     Show version information\n";
}