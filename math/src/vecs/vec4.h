#pragma once

#include "compile_header.h"
#include <type_traits>
#include "vec3.h"

namespace KMath
{

template<class TReal>
requires std::is_arithmetic_v<TReal>
class KVec4
{
public:
    KVec4() = default;
    KVec4(TReal x, TReal y, TReal z, TReal w) : x(x), y(y), z(z), w(w) { }
    explicit KVec4(KVec3<TReal> vec) : x(vec.X()), y(vec.Y()), z(vec.Z), w(1) { }
    KVec4(const KVec4&) = default;
    KVec4(KVec4&&) = default;
    KVec4& operator=(const KVec4&) = default;
    KVec4& operator=(KVec4&&) = default;

    KVec3<TReal> ToVec3() const { return KVec3<TReal> { x/w, y/w, z/w }; }

    const TReal& X() const { return x; }
    const TReal& Y() const { return y; }
    const TReal& Z() const { return z; }
    const TReal& W() const { return w; }

    TReal& X() { return x; }
    TReal& Y() { return y; }
    TReal& Z() { return z; }
    TReal& W() { return w; }

    const TReal* XYZW() const { return xyzw; }

protected:
    union
    {
        struct { TReal x, y, z, w; };

        TReal xyzw[4];
    };
};

}