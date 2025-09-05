#include "AddressLoader.hpp"
#include "FileHandler.hpp"
#include <sstream>

std::vector<std::string> sr2::AddressLoader::s_HTTPAddresses;
std::vector<std::string> sr2::AddressLoader::s_TORAddresses;
std::vector<std::string> sr2::AddressLoader::s_NOSTRelays;

void sr2::AddressLoader::LoadHTTPAddresses()
{
    std::string addresses;
    FileHandler::ReadTextFile("/etc/sr2/http.remotes", &addresses);
    SplitString(&s_HTTPAddresses, addresses, '\n');
}

void sr2::AddressLoader::LoadTORAddresses()
{
    std::string addresses;
    FileHandler::ReadTextFile("/etc/sr2/tor.remotes", &addresses);
    SplitString(&s_TORAddresses, addresses, '\n');
}

void sr2::AddressLoader::LoadNOSTRelays()
{
    std::string relays;
    FileHandler::ReadTextFile("/etc/sr2/nostr.remotes", &relays);
    SplitString(&s_NOSTRelays, relays, '\n');
}

std::string sr2::AddressLoader::GetHTTPAddress(size_t index)
{
    if(s_HTTPAddresses.size() == 0)
        return "";
    if (index >= s_HTTPAddresses.size())
        return s_HTTPAddresses[(s_HTTPAddresses.size() - 1)];
    return s_HTTPAddresses[index];
}

std::string sr2::AddressLoader::GetTORAddress(size_t index)
{
    if(s_TORAddresses.size() == 0)
        return "";
    if (index >= s_TORAddresses.size())
        return s_TORAddresses[(s_TORAddresses.size() - 1)];
    return s_TORAddresses[index];
}

std::string sr2::AddressLoader::GetNOSTRelay(size_t index)
{
    if(s_NOSTRelays.size() == 0)
        return "";
    if (index >= s_NOSTRelays.size())
        return s_NOSTRelays[(s_NOSTRelays.size() - 1)];
    return s_NOSTRelays[index];
}

void sr2::AddressLoader::SplitString(std::vector<std::string>* output, const std::string& s, char delimiter)
{
    std::istringstream iss(s);
    std::string token;
    while (std::getline(iss, token, delimiter)) {
        if(token.length() > 0)
            output->push_back(token);
    }
    //return tokens;
} 
