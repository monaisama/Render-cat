#pragma once

#include <type_traits>

namespace KMath
{

template<class TELE>
requires std::is_arithmetic_v<TELE>
class KVec4
{
public:
    KVec4() = default;
    KVec4(TELE x, TELE y, TELE z, TELE w)
    {
        ele.xyzw.x = x;
        ele.xyzw.y = y;
        ele.xyzw.z = z;
        ele.xyzw.w = w;
    }

    TELE X() const { return ele.xyzw.x; }
    TELE Y() const { return ele.xyzw.y; }
    TELE Z() const { return ele.xyzw.z; }
    TELE W() const { return ele.xyzw.w; }

    TELE& X() { return ele.xyzw.x; }
    TELE& Y() { return ele.xyzw.y; }
    TELE& Z() { return ele.xyzw.z; }
    TELE& W() { return ele.xyzw.w; }

    const TELE* XYZW() const { return ele.arr; }

protected:
    union
    {
        struct { TELE x, y, z, w; } xyzw;

        struct { TELE r, g, b, a; } rgba;

        TELE arr[4];
    } ele;
};

}