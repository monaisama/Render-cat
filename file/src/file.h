#pragma once
#include "compile_header.h"
#include <string>
#include <fstream>

namespace KFileUtils
{

class K_API KFileTest
{
public:
    KFileTest() = default;
    int32_t Int() const;

protected:
    int32_t ELe;
};

class K_API KFile
{
public:
    KFile() = default;
    bool Open(const std::string& fileName);
    int32_t Read(std::string& content);
    void Write(const std::string& str);
    void Close();

    std::fstream& GetStream() { return file; }

    static std::string ReadFile(const std::string& fileName, int32_t* length = nullptr);

protected:
    std::fstream file;
};

}