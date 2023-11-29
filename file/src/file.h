#pragma once
#include "compile_header.h"
#include <string>
#include <fstream>
#include <string_view>

namespace KFileUtils
{

class K_API KFile
{
public:
    KFile();
    KFile(const KFile&) = default;
    KFile(KFile&&);
    KFile& operator=(const KFile&) = delete;
    KFile& operator=(KFile&&);
    ~KFile();

    bool IsValid() const;
    operator bool() const;

    KFile& Open(std::string_view fileName, std::ios::openmode mode = std::ios::out);
    size_t Read(std::string& content);
    void Write(std::string_view str);
    void Close();

    std::fstream& GetStream() { return stream; }

    static std::string ReadFile(std::string_view fileName, int32_t* length = nullptr);
    static KFile OpenFile(std::string_view filepath, std::ios::openmode mode = std::ios::out);

protected:
    std::fstream stream;
};

}