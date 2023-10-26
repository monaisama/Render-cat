#pragma once
#include "compile_header.h"
#include <iostream>
#include <string>

namespace KLog
{
K_API void Log(const char*);

K_API void Log(const std::string&);
}