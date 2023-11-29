#include "file.h"
#include "log.h"

#include <cstdint>
#include <exception>

namespace KFileUtils
{

KFile::KFile()
    : stream {}
{
    auto mask = std::fstream::failbit | std::fstream::badbit;
    stream.exceptions(mask);
}

KFile& KFile::Open(std::string_view fileName)
{
    try
    {
        stream = std::fstream(fileName.data(), std::fstream::in | std::fstream::out);
        if (!stream)
            throw std::exception("create file stream failed.");
    }
    catch(const std::exception& e)
    {
        KLog::LogError("open file failed. path: {0}, message: {1}", fileName, e.what());
    }
    
    return *this;
}

KFile::KFile(KFile&& file)
    : stream(std::move(file.stream))
{
}

KFile::~KFile()
{
    Close();
}

KFile& KFile::operator=(KFile&& file)
{
    Close();
    stream = std::move(file.stream);
    return *this;
}

bool KFile::IsValid() const
{
    return stream && stream.is_open();
}

KFile::operator bool() const
{
    return IsValid();
}

size_t KFile::Read(std::string& content)
{
    if (!IsValid())
    {
        KLog::LogError("File is not valid to read.");
        return 0;
    }
    char cache[1024];
    size_t count = 0;
    while (stream.read(cache, 1024))
    {
        content.append(cache, 0, stream.gcount());
        count += stream.gcount();
    }
    content.append(cache, 0, stream.gcount());
    count += stream.gcount();
    return count;
}

void KFile::Write(std::string_view str)
{
    if (!IsValid())
    {
        KLog::LogError("File is not valid to write");
        return;
    }
    stream.write(str.data(), str.length());
    stream.flush();
}

void KFile::Close()
{
    if (IsValid())
        stream.close();
}

std::string KFile::ReadFile(std::string_view fileName, int32_t* length)
{
    KFile file;

    try
    {
        file.Open(fileName);
    }
    catch(const std::exception& e)
    {
        KLog::LogError("file is not valid, readfile failed. {0}", fileName);
        return {};
    }
    
    if (!file)
    {
        KLog::LogError("file is not valid, readfile failed. {0}", fileName);
        return {};
    }

    std::string content;
    int32_t count = file.Read(content);
    if (length)
        *length = count;
    file.Close();

    return content;
}

KFile KFile::OpenFile(std::string_view filepath)
{
    return std::move(KFile{}.Open(filepath));
}

}