#include "Samples.hpp"
#include <sqlite3.h>
#include <iostream>
#include <cm3p/curl/curl.h>

// Callback function to write the received data into a std::string
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t totalSize = size * nmemb;
    std::string* str = static_cast<std::string*>(userp);
    str->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

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
    std::string response;

    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        // Set URL
        curl_easy_setopt(curl, CURLOPT_URL, "https://jsonplaceholder.typicode.com/posts/1");

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
        else {
            std::cout << "Response:\n" << response << std::endl;
        }

        // Cleanup
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
}
