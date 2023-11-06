#pragma once
#include "compile_header.h"
#include <type_traits>

namespace KMath
{

template<class TELE>
requires std::is_arithmetic_v<TELE>
class KVec3
{
public:
    KVec3() = default;
    KVec3(TELE x, TELE y, TELE z)
    {
        ele.xyz.x = x;
        ele.xyz.y = y;
        ele.xyz.z = z;
    }

    KVec3 operator+(const KVec3& other)
    {
        KVec3 ret;
        ret.X() = X() + other.X();
        ret.Y() = Y() + other.Y();
        ret.Z() = Z() + other.Z();
        return ret;
    }

    KVec3 operator+=(const KVec3& other)
    {
        X() += other.X();
        Y() += other.Y();
        Z() += other.Z();
        return *this;
    }

    TELE X() const { return ele.xyz.x; }
    TELE Y() const { return ele.xyz.y; }
    TELE Z() const { return ele.xyz.z; }

    TELE& X() { return ele.xyz.x; }
    TELE& Y() { return ele.xyz.y; }
    TELE& Z() { return ele.xyz.z; }

    const TELE* XYZ() const { return ele.arr; }

public:
    union
    {
        struct { TELE x, y, z; } xyz;

        struct { TELE r, g, b; } rgb;

        TELE arr[3];
    } ele;
};

using KVec3f = KVec3<float>;

}