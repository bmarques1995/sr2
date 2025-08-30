#include "FileHandler.hpp"
#include <fstream>

bool sr2::FileHandler::ReadTextFile(std::string_view path, std::string* content)
{
	bool loaded = false;
	std::ifstream fileStream;
	fileStream.exceptions(std::ifstream::badbit | std::ifstream::failbit);
	try
	{
		fileStream.open(path.data(), std::ios::binary);
		loaded = true;
	}
	catch (...)
	{
		return loaded;
	}
	auto start = fileStream.tellg();
	fileStream.seekg(0, std::ios::end);
	uint64_t fsize = fileStream.tellg() - start;
	fileStream.seekg(0, std::ios::beg);
	char* buffer = new char[fsize + 1];
	buffer[fsize] = '\0';
	fileStream.read(buffer, fsize);
	*content = buffer;
	delete[] buffer;
	return loaded;
}

bool sr2::FileHandler::WriteTextFile(std::string_view path, std::string content)
{
	bool stored = false;
	std::ofstream fileStream;
	fileStream.exceptions(std::ofstream::badbit | std::ofstream::failbit);
	try
	{
		fileStream.open(path.data(), std::ios::out | std::ios::binary);
		stored = true;
	}
	catch (...)
	{
		return stored;
	}
	fileStream << content;
	return stored;
}

bool sr2::FileHandler::ReadBinFile(std::string_view path, std::byte** content, size_t* fileSize)
{
	bool loaded = false;
	std::ifstream fileStream;
	fileStream.exceptions(std::ifstream::badbit | std::ifstream::failbit);
	try
	{
		fileStream.open(path.data(), std::ios::binary);
		loaded = true;
	}
	catch (...)
	{
		return loaded;
	}
	auto start = fileStream.tellg();
	fileStream.seekg(0, std::ios::end);
	uint64_t fsize = fileStream.tellg() - start;
	*fileSize = fsize;
	fileStream.seekg(0, std::ios::beg);
	*content = new std::byte[fsize];
	fileStream.read(reinterpret_cast<char*>(*content), fsize);
	return loaded;
}

bool sr2::FileHandler::WriteBinFile(std::string_view path, std::byte* content, size_t dataSize)
{
	bool stored = false;
	std::ofstream fileStream;
	fileStream.exceptions(std::ofstream::badbit | std::ofstream::failbit);
	try
	{
		fileStream.open(path.data(), std::ios::out | std::ios::binary);
		stored = true;
	}
	catch (...)
	{
		return stored;
	}
	fileStream.write(reinterpret_cast<char*>(content), dataSize);
	return stored;
}

bool sr2::FileHandler::ReadBinFile(std::string_view path, std::shared_ptr<RawBuffer>* content)
{
	bool loaded = false;
	std::ifstream fileStream;
	fileStream.exceptions(std::ifstream::badbit | std::ifstream::failbit);
	try
	{
		fileStream.open(path.data(), std::ios::binary);
		loaded = true;
	}
	catch (...)
	{
		return loaded;
	}
	auto start = fileStream.tellg();
	fileStream.seekg(0, std::ios::end);
	uint64_t fsize = fileStream.tellg() - start;
	fileStream.seekg(0, std::ios::beg);
	uint8_t* buffer = new uint8_t[fsize];
	fileStream.read(reinterpret_cast<char*>(buffer), fsize);
	*content = std::make_shared<RawBuffer>(buffer, fsize);
	delete[] buffer;
	return loaded;
}

bool sr2::FileHandler::WriteBinFile(std::string_view path, const std::shared_ptr<RawBuffer>& content)
{
	bool stored = false;
	std::ofstream fileStream;
	fileStream.exceptions(std::ofstream::badbit | std::ofstream::failbit);
	try
	{
		fileStream.open(path.data(), std::ios::out | std::ios::binary);
		stored = true;
	}
	catch (...)
	{
		return stored;
	}
	fileStream.write(reinterpret_cast<const char*>(content->GetData()), content->GetSize());
	return stored;
}

bool sr2::FileHandler::FileExists(std::string_view path)
{
	bool loaded = false;
	std::ifstream fileStream;
	fileStream.exceptions(std::ifstream::failbit);
	try
	{
		fileStream.open(path.data(), std::ios::binary);
		loaded = true;
		fileStream.close();
	}
	catch (...)
	{
	}
	return loaded;
}
