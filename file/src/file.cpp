#include "file.h"
#include "log.h"

#include <cstdint>

namespace KFileUtils
{

int32_t KFileTest::Int() const
{
    return ELe + 1;
}

bool KFile::Open(const std::string& fileName)
{
    // todo.. 需要判定文件是否存在，并且需要给定选项删除文件里面的内容再写入新的
    file = std::fstream(fileName, std::fstream::in | std::fstream::out);
    return true;
}

int32_t KFile::Read(std::string& content)
{
    char cache[1024];
    int32_t count = 0;
    while (file.read(cache, 1024))
    {
        content.append(cache, 0, file.gcount());
        count += file.gcount();
    }
    content.append(cache, 0, file.gcount());
    count += file.gcount();
    return count;
}

void KFile::Write(const std::string& str)
{
    file.write(str.c_str(), str.length());
    file.flush();
}

void KFile::Close()
{
    file.close();
}

std::string KFile::ReadFile(const std::string& fileName, int32_t* length)
{
    KFile file;
    file.Open(fileName);

    std::string content;
    int32_t count = file.Read(content);
    if (length)
        *length = count;
    file.Close();

    return std::move(content);
}

}