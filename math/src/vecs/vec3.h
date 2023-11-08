#pragma once
#include "compile_header.h"
#include <type_traits>

namespace KMath
{

template<class TELE>
requires std::is_arithmetic_v<TELE>
class KVec3
{
    using KReal = TELE;
public:
    KVec3() = default;
    KVec3(KReal x, KReal y, KReal z) : x(x), y(y), z(z) { }

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

    const KReal& X() const { return x; }
    const KReal& Y() const { return y; }
    const KReal& Z() const { return z; }

    KReal& X() { return x; }
    KReal& Y() { return y; }
    KReal& Z() { return z; }

    const KReal* XYZ() const { return xyz; }

public:
    union
    {
        struct { KReal x, y, z; };

        KReal xyz[3];
    };
};

using KVec3f = KVec3<float>;

}