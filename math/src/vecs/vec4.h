#pragma once

#include "compile_header.h"
#include "vec3.h"
#include <type_traits>

namespace KMath
{

template<class TReal>
requires std::is_arithmetic_v<TReal>
class KVec4
{
public:
    K_API static const KVec4 zero;
    K_API static const KVec4 wzero;

public:
    KVec4() = default;
    KVec4(TReal x, TReal y, TReal z, TReal w) : x(x), y(y), z(z), w(w) { }
    explicit KVec4(const KVec3<TReal>& vec, TReal w = 0) : x(vec.X()), y(vec.Y()), z(vec.Z()), w(w) { }
    KVec4(const KVec4&) = default;
    KVec4(KVec4&&) = default;
    KVec4& operator=(const KVec4&) = default;
    KVec4& operator=(KVec4&&) = default;

    template<class TValue> requires std::is_arithmetic_v<TValue>
    KVec4 operator*(TValue value) const
    {
        return KVec4 {
            static_cast<TReal>(x * value),
            static_cast<TReal>(y * value),
            static_cast<TReal>(z * value),
            static_cast<TReal>(w * value)
        };
    }
    template<class TValue> requires std::is_arithmetic_v<TValue>
    KVec4& operator*=(TValue value)
    {
        x = static_cast<TReal>(x * value);
        y = static_cast<TReal>(y * value);
        x = static_cast<TReal>(z * value);
        w = static_cast<TReal>(w * value);
        return *this;
    }

    TReal operator*(const KVec4& rhs) const
    {
        return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
    }
    static TReal Dot(const KVec4& lhs, const KVec4& rhs) { return lhs * rhs; }

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
    friend std::ostream& operator<<(std::ostream& out, const KVec4& rhs)
    {
        out << "{" << rhs.x << " " << rhs.y << " " << rhs.z << " " << rhs.w << "}";
        return out;
    }

protected:
    union
    {
        struct { TReal x, y, z, w; };

        TReal xyzw[4];
    };
};

}