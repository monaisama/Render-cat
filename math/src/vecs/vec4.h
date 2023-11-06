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

    const TELE& X() const { return ele.xyzw.x; }
    const TELE& Y() const { return ele.xyzw.y; }
    const TELE& Z() const { return ele.xyzw.z; }
    const TELE& W() const { return ele.xyzw.w; }

    TELE& X() { return ele.xyzw.x; }
    TELE& Y() { return ele.xyzw.y; }
    TELE& Z() { return ele.xyzw.z; }
    TELE& W() { return ele.xyzw.w; }

    const TELE* XYZW() const { return ele.arr; }

protected:
    union
    {
        struct { TELE x, y, z, w; } xyzw;

        TELE arr[4];
    } ele;
};

}