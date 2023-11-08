#pragma once

#include <type_traits>

namespace KMath
{

template<class TELE>
requires std::is_arithmetic_v<TELE>
class KVec4
{
    using KReal = TELE;
public:
    KVec4() = default;
    KVec4(KReal x, KReal y, KReal z, KReal w) : x(x), y(y), z(z), w(w) { }

    const KReal& X() const { return x; }
    const KReal& Y() const { return y; }
    const KReal& Z() const { return z; }
    const KReal& W() const { return w; }

    KReal& X() { return x; }
    KReal& Y() { return y; }
    KReal& Z() { return z; }
    KReal& W() { return w; }

    const KReal* XYZW() const { return xyzw; }

protected:
    union
    {
        struct { KReal x, y, z, w; };

        KReal xyzw[4];
    };
};

}