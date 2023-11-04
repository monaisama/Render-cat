#pragma once
#include "log.h"

// void func(int32_t n)
// {
//     KLog::Log(n);
// }

void func();

template<class T>
void tfunc(T t)
{
    KLog::Log(t);
}