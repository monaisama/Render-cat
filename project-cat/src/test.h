#pragma once
#include <iostream>

void TestCompileConfig()
{
#if defined(KDEBUG)
    std::cout << "debug_mode open." << std::endl;
#endif
}
