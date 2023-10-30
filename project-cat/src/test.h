#pragma once
#include <iostream>

void TestCompileConfig()
{
#if KDEBUG
    std::cout << "debug_mode open." << std::endl;
#endif
}
