#pragma once

#include <type_traits>

namespace KMath
{

template<class TReal>
requires std::is_arithmetic_v<TReal>
class KVec4
{
public:
    KVec4() = default;
    KVec4(TReal x, TReal y, TReal z, TReal w) : x(x), y(y), z(z), w(w) { }

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