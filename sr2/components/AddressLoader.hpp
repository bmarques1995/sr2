#pragma once

#include <vector>
#include <string>
#include <cstdlib>

namespace sr2
{
    class AddressLoader
    {
    public:
        static void LoadHTTPAddresses();
        static void LoadTORAddresses();
        static void LoadNOSTRelays();

        static std::string GetHTTPAddress(size_t index);
        static std::string GetTORAddress(size_t index);
        static std::string GetNOSTRelay(size_t index);
    private:
        static void SplitString(std::vector<std::string>* output, const std::string& s, char delimiter);

        static std::vector<std::string> s_HTTPAddresses;
        static std::vector<std::string> s_TORAddresses;
        static std::vector<std::string> s_NOSTRelays;
    };
}
