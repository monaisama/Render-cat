#include "log.h"

namespace KLog
{
void Log(const char* src)
{
    std::cout << src << std::endl;
}

void Log(const std::string& src)
{
    Log(src.c_str());
}
}