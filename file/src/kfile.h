#pragma once
#include "compile_header.h"
#include <string>
#include <fstream>

class K_API KFile
{
public:
    bool Open(const std::string& fileName);
    int32_t Read(std::string& content);
    void Close();

    static std::string ReadFile(const std::string& fileName, int32_t* length = nullptr);

protected:
    std::ifstream file;
};