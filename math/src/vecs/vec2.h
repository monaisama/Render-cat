#pragma once

#include <type_traits>

template<class TELE>
requires std::is_arithmetic_v<TELE>
class KVec2
{
    using KReal = TELE;
public:
    KVec2() = default;
    KVec2(KReal x, KReal y) : x(x), y(y) { }

    const KReal& X() const { return x; }
    const KReal& Y() const { return y; }

    KReal& X() { return x; }
    KReal& Y() { return y; }

    const KReal* XY() { return xy; }

protected:
    union
    {
        struct { KReal x, y; };

        KReal xy[2];
    };
    
};
