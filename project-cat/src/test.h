#pragma once
#include <iostream>
#include "file.h"
#include "log.h"

void TestCompileConfig()
{
#if KDEBUG
    std::cout << "debug_mode open." << std::endl;
#endif
}

void TestFunc()
{
    // KLog::Log(KFile::ReadFile("default.vs"));
    // KLog::Log(KFile::ReadFile("default_color.fs"));
    // KLog::Log(KFile::ReadFile("blue_color.fs"));
}