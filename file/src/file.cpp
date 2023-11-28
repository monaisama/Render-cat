#include "file.h"
#include "log.h"

#include <cstdint>

namespace KFileUtils
{

int32_t KFileTest::Int() const
{
    return ELe + 1;
}

KFile& KFile::Open(std::string_view fileName)
{
    // todo.. 需要判定文件是否存在，并且需要给定选项删除文件里面的内容再写入新的
    stream = std::fstream(fileName.data(), std::fstream::in | std::fstream::out);
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

size_t KFile::Read(std::string& content)
{
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
    stream.write(str.data(), str.length());
    stream.flush();
}

void KFile::Close()
{
    if (stream.is_open())
        stream.close();
}

std::string KFile::ReadFile(std::string_view fileName, int32_t* length)
{
    KFile file;
    file.Open(fileName);

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