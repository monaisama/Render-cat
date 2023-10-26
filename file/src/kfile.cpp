#include "kfile.h"
#include "klog.h"

bool KFile::Open(const std::string& fileName)
{
    KLog::Log("open file.");
    file = std::ifstream(fileName, std::ios::in);
    return true;
}

int32_t KFile::Read(std::string& content)
{
    KLog::Log("read file.");
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
    KLog::Log("close file.");
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