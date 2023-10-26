#include "kfile.h"

#include "klog.h"

bool KFile::Open(const std::string& fileName)
{
    KLog::Log("open file.");
    return true;
}

int32_t KFile::Read(std::string& fileName)
{
    KLog::Log("read file.");
    return 0;
}

void KFile::Close()
{
    KLog::Log("close file.");
}