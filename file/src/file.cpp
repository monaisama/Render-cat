#include "file.h"
#include "log.h"

KFile::KFile()
{
}

bool KFile::Open(const std::string& fileName)
{
    file = std::ifstream(fileName, std::ifstream::in);
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