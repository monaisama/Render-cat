#pragma once
#include <iostream>
#include "kfile.h"

void TestCompileConfig()
{
#if KDEBUG
    std::cout << "debug_mode open." << std::endl;
#endif
}

void TestFunc()
{
    KFile file;
    file.Open("name.txt");
    file.Close();
}