#pragma once
#include "compile_header.h"

namespace KMath
{

template<class TELE>
class KVec3
{
    using ElementType = TELE;

public:
    KVec3() = default;
    KVec3(ElementType x, ElementType y, ElementType z) : x(x), y(y), z(z) { }

    KVec3 operator+(const KVec3& other)
    {
        KVec3 ret;
        ret.x = x + other.x;
        ret.y = y + other.y;
        ret.z = y + other.z;
        return ret;
    }

    KVec3 operator+=(const KVec3& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

public:
    ElementType x, y, z;
};

using KVec3f = KVec3<float>;

}