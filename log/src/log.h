#pragma once
#include "compile_header.h"
#include <iostream>
#include <string>

namespace KLog
{
    
template<class TParam> void Log(TParam p)
{
    std::cout << p << std::endl;
}

K_API void Log(const char*);

K_API void Log(const std::string&);

}