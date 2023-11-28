#pragma once
#include "compile_header.h"
#include <string>
#include <fstream>
#include <string_view>

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
    KFile(const KFile&) = default;
    KFile(KFile&&);
    KFile& operator=(const KFile&) = delete;
    KFile& operator=(KFile&&);
    ~KFile();

    KFile& Open(std::string_view fileName);
    size_t Read(std::string& content);
    void Write(std::string_view str);
    void Close();

    std::fstream& GetStream() { return stream; }

    static std::string ReadFile(std::string_view fileName, int32_t* length = nullptr);
    static KFile OpenFile(std::string_view filepath);

protected:
    std::fstream stream;
};

}