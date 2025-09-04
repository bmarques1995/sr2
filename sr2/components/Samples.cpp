#include "Samples.hpp"
#include <sqlite3.h>
#include <iostream>
#include <memory>
#include <curl/curl.h>
#include <cstring>
#include <cstdlib>
#include "RawBuffer.hpp"
#include "Downloader.hpp"
#include "CURLStarter.hpp"
#include "FileHandler.hpp"

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
    CURLStarter::InitCurl();
    CURLStarter::SetCertificateLocation("/etc/ssl/certs/ca-certificates.crt");
    Downloader downloader;
    std::shared_ptr<sr2::RawBuffer> m_OutputBuffer;
    m_OutputBuffer.reset(new sr2::RawBuffer());
    downloader.DownloadFile("https://pbs.twimg.com/media/GA8Wn6VXQAAZ63z?format=jpg&name=900x900");
    downloader.PackMemoryChunks(&m_OutputBuffer);
    std::string filename = "response." + downloader.ReturnMappedMime();
    FileHandler::WriteBinFile(filename, m_OutputBuffer);
    CURLStarter::ShutdownCurl();
}
