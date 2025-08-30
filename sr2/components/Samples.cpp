#include "Samples.hpp"
#include <sqlite3.h>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <cm3p/curl/curl.h>
#include <vector>
#include <cstring>
#include <cstdlib>
#include "FileHandler.hpp"
#include "Chunk.hpp"
#include "RawBuffer.hpp"

uint32_t download_chunk = 0;

const std::unordered_map<std::string, std::string> mime_extension_map = {
    {"application/json", "json"},
    {"application/json; charset=utf-8", "json"},
    {"text/html", "html"},
    {"text/plain", "txt"},
    {"image/png", "png"},
    {"image/jpeg", "jpg"},
};

// Callback function to write the received data into a std::string
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    size_t bufferSize = size * nmemb;
    std::shared_ptr<sr2::Chunk> chunk;
    chunk.reset(new sr2::Chunk(download_chunk));
    chunk->RecreateBuffer((uint8_t*)contents, bufferSize);
    std::vector<std::shared_ptr<sr2::Chunk>>* buffer = static_cast<std::vector<std::shared_ptr<sr2::Chunk>>*>(userp);
    buffer->push_back(chunk);
    download_chunk++;
    return bufferSize;
}

void pack_memory_chunks(const std::vector<std::shared_ptr<sr2::Chunk>>& chunks, std::shared_ptr<sr2::RawBuffer>* out_buffer);

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

void sr2::RequestSampleContent()
{
    CURL* curl;
    CURLcode res;
    std::vector<std::shared_ptr<sr2::Chunk>> response;

    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        // Set URL
        curl_easy_setopt(curl, CURLOPT_URL, "https://pbs.twimg.com/media/GA8Wn6VXQAAZ63z?format=jpg&name=900x900");

#ifndef WIN32
        // Debian CA certificates (system bundle)
        curl_easy_setopt(curl, CURLOPT_CAINFO, "/etc/ssl/certs/ca-certificates.crt");
#endif
        // Set write callback
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

        // Set pointer to store the response
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Perform the request
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: "
                << curl_easy_strerror(res) << std::endl;
        }

        // Check HTTP status code
        long http_code = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        if (http_code != 200) {
            std::cerr << "Unexpected HTTP status: " << http_code << "\n";
            curl_easy_cleanup(curl);
            return;
        }

        // Check MIME type
        char* content_type = nullptr;
        curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &content_type);
        std::string mime_str = content_type ? std::string(content_type) : "";
        auto it = mime_extension_map.find(mime_str);
        if (it != mime_extension_map.end()) {
            std::cout << response.size() << "\n";
            std::string file_name = "response." + it->second;
            std::shared_ptr<sr2::RawBuffer> response_pack;
            response_pack.reset(new sr2::RawBuffer());
            pack_memory_chunks(response, &response_pack);
            FileHandler::WriteBinFile(file_name, response_pack);
        }

        std::cout << "Response OK, MIME type matches:\n";

        // Cleanup
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
}

void pack_memory_chunks(const std::vector<std::shared_ptr<sr2::Chunk>>& chunks, std::shared_ptr<sr2::RawBuffer>* out_buffer)
{
    if (chunks.empty() || out_buffer == nullptr)
        return;

    size_t total_size = 0;
    for (const auto& chunk : chunks)
    {
        total_size += chunk->GetSize();
    }

    uint8_t* combined_data = new uint8_t[total_size];
    size_t offset = 0;
    for (const auto& chunk : chunks)
    {
        memcpy(combined_data + offset, chunk->GetData(), chunk->GetSize());
        offset += chunk->GetSize();
    }

    (*out_buffer)->RecreateBuffer(combined_data, total_size);
    delete[] combined_data;
}