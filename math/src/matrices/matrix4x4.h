#pragma once

#include "compile_header.h"
#include "vec.h"
#include <iostream>
#include <type_traits>

namespace KMath
{

template<class TReal>
requires std::is_arithmetic_v<TReal>
class KMatrix4x4
{
public:
    K_API static const KMatrix4x4 identity;
    K_API static const KMatrix4x4 zero;

public:
    KMatrix4x4() = default;

protected:
    union
    {
        
    };
};

}
