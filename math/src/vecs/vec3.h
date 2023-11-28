#pragma once
#include "compile_header.h"
#include "patterns.h"
#include <type_traits>
#include "mymath.h"
#include "log.h"
#include <iostream>
#include "vec2.h"

namespace KMath
{

// 左手坐标系，并且z轴向上，x轴向前，y轴向右(按照面向来说)
template<std::KReal TReal>
class KVec3
{
public:
    K_API static const KVec3 up; // z
    K_API static const KVec3 right; // y
    K_API static const KVec3 forward; // x
    K_API static const KVec3 zero;
    K_API static const KVec3 wzero;
    K_API static const KVec3 one;

    GEN_DEFAULT_CONTRUCTOR_CODE_DEFAULT(KVec3)

public:
    KVec3(TReal x, TReal y, TReal z) : x(x), y(y), z(z) { }
    explicit KVec3(const KVec2<TReal>& vec2, TReal w = 0) : x(vec2.X()), y(vec2.Y()), z(w) { }

    const TReal& X() const { return x; }
    const TReal& Y() const { return y; }
    const TReal& Z() const { return z; }

    TReal& X() { return x; }
    TReal& Y() { return y; }
    TReal& Z() { return z; }

    const TReal* XYZ() const { return xyz; }
    
    KVec3 operator+(const KVec3& rhs) const { return KVec3 { x + rhs.x, y + rhs.y, z + rhs.z }; }
    KVec3& operator+=(const KVec3& rhs) { x += rhs.x; y += rhs.y; z += rhs.z; return *this; }

    KVec3 operator-(const KVec3& rhs) const { return KVec3 { x - rhs.x, y - rhs.y, z - rhs.z }; }
    KVec3& operator-=(const KVec3& rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this; }

    KVec3& operator-() { return *this *= -1; }
    KVec3 operator-() const { return *this * -1; }

    template<std::KReal TValue = TReal>
    KVec3 operator*(TValue value) const
    {
        return KVec3 {
            static_cast<TReal>(value * x),
            static_cast<TReal>(value * y),
            static_cast<TReal>(value * z)
        };
    }
    template<std::KReal TValue = TReal>
    KVec3& operator*=(TValue value)
    {
        x = static_cast<TReal>(value * x);
        y = static_cast<TReal>(value * y);
        z = static_cast<TReal>(value * z);
        return *this;
    }
    template<std::KReal TValue = TReal>
    KVec3 operator/(TValue value) const
    {
        if (EqualsZero(value))
        {
            KLog::LogSimpleError("divide zero error.");
            return *this;
        }
        return KVec3 {
            static_cast<TReal>(x / value),
            static_cast<TReal>(y / value),
            static_cast<TReal>(z / value)
        };
    }
    template<std::KReal TValue = TReal>
    KVec3& operator/=(TValue value)
    {
        if (EqualsZero(value))
        {
            KLog::LogSimpleError("divide zero error.");
            return *this;
        }
        x = static_cast<TReal>(x / value);
        y = static_cast<TReal>(y / value);
        z = static_cast<TReal>(z / value);
        return *this;
    }

    bool operator==(const KVec3& rhs) const { return Equals(x, rhs.x) && Equals(y, rhs.y) && Equals(z, rhs.z); }
    bool operator!=(const KVec3& rhs) const { return !(*this == rhs); }

    // 点乘
    TReal operator*(const KVec3& rhs) const { return x * rhs.x + y * rhs.y + z * rhs.z; }
    static TReal Dot(const KVec3& lhs, const KVec3& rhs) { return lhs * rhs; }

    // 叉乘 推导类似vec2 也是用分配率展开，然后根据ijk三个轴消除
    KVec3 operator^(const KVec3& rhs) const
    {
        return KVec3 {
            y * rhs.z - z * rhs.y,
            z * rhs.x - x * rhs.z,
            x * rhs.y - y * rhs.x
        };
    }
    static KVec3 Cross(const KVec3& lhs, const KVec3& rhs) { return lhs ^ rhs; }

    KVec3& Normalize()
    {
        if constexpr (std::is_integral_v<TReal>)
        {
            KLog::LogSimpleWarning("maybe loss of presion warning.");
        }
        float length = Length();
        if (NearlyZero(length))
            return *this;
        return *this /= length;
    }

    float Length() const { return sqrt(static_cast<float>(SqrtLength())); }
    TReal SqrtLength() const { return x * x + y * y + z * z; }

protected:
    friend std::ostream& operator<<(std::ostream& out, const KVec3& rhs)
    {
        out << "{ " << rhs.x << ", " << rhs.y << ", " << rhs.z << " }";
        return out;
    }

public:
    union
    {
        struct { TReal x, y, z; };

        TReal xyz[3];
    };
};

}