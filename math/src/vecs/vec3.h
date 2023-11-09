#pragma once
#include "compile_header.h"
#include <type_traits>
#include "mymath.h"
#include "log.h"
#include <iostream>

namespace KMath
{

// 左手坐标系，并且z轴向上，x轴向前，y轴向右(按照面向来说)
template<class TELE>
requires std::is_arithmetic_v<TELE>
class KVec3
{
    using KReal = TELE;
public:
    K_API static const KVec3 up; // z
    K_API static const KVec3 right; // y
    K_API static const KVec3 forward; // x
    K_API static const KVec3 zero;

public:
    KVec3() = default;
    KVec3(KReal x, KReal y, KReal z) : x(x), y(y), z(z) { }
    KVec3(const KVec3&) = default;
    KVec3(KVec3&&) = default;
    KVec3& operator=(const KVec3&) = default;
    KVec3& operator=(KVec3&&) = default;

    const KReal& X() const { return x; }
    const KReal& Y() const { return y; }
    const KReal& Z() const { return z; }

    KReal& X() { return x; }
    KReal& Y() { return y; }
    KReal& Z() { return z; }

    const KReal* XYZ() const { return xyz; }
    
    KVec3 operator+(const KVec3& rhs) const { return KVec3 { x + rhs.x, y + rhs.y, z + rhs.z }; }
    KVec3& operator+=(const KVec3& rhs) { x += rhs.x; y += rhs.y; z += rhs.z; return *this; }

    KVec3 operator-(const KVec3& rhs) const { return KVec3 { x - rhs.x, y - rhs.y, z - rhs.z }; }
    KVec3& operator-=(const KVec3& rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this; }

    KVec3& operator-() { return *this *= -1; }

    template<class TValue> requires std::is_arithmetic_v<TValue>
    KVec3 operator*(TValue value) const
    {
        return KVec3 {
            static_cast<KReal>(value * x),
            static_cast<KReal>(value * y),
            static_cast<KReal>(value * z)
        };
    }
    template<class TValue> requires std::is_arithmetic_v<TValue>
    KVec3& operator*=(TValue value)
    {
        x = static_cast<KReal>(value * x);
        y = static_cast<KReal>(value * y);
        z = static_cast<KReal>(value * z);
        return *this;
    }
    template<class TValue> requires std::is_arithmetic_v<TValue>
    KVec3 operator/(TValue value) const
    {
        if (EqualsZero(value))
        {
            KLog::LogSimpleError("divide zero error.");
            return *this;
        }
        return KVec3 {
            static_cast<KReal>(x / value),
            static_cast<KReal>(y / value),
            static_cast<KReal>(z / value)
        };
    }
    template<class TValue> requires std::is_arithmetic_v<TValue>
    KVec3& operator/=(TValue value)
    {
        if (EqualsZero(value))
        {
            KLog::LogSimpleError("divide zero error.");
            return *this;
        }
        x = static_cast<KReal>(x / value);
        y = static_cast<KReal>(y / value);
        z = static_cast<KReal>(z / value);
        return *this;
    }

    bool operator==(const KVec3& rhs) const { return Equals(x, rhs.x) && Equals(y, rhs.y) && Equals(z, rhs.z); }
    bool operator!=(const KVec3& rhs) const { return !(*this == rhs); }

    // 点乘
    KReal operator|(const KVec3& rhs) const { return x * rhs.x + y * rhs.y + z * rhs.z; }
    static KReal Dot(const KVec3& lhs, const KVec3& rhs) { return lhs | rhs; }

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
        if constexpr (std::is_integral_v<KReal>)
        {
            KLog::LogSimpleWarning("maybe loss of presion warning.");
        }
        float length = Length();
        if (NearlyZero(length))
            return *this;
        return *this /= length;
    }

    float Length() const { return sqrt(static_cast<float>(SqrtLength())); }
    KReal SqrtLength() const { return x * x + y * y + z * z; }

protected:
    friend std::ostream& operator<<(std::ostream& out, const KVec3& rhs)
    {
        out << "{ " << rhs.x << ", " << rhs.y << ", " << rhs.z << " }";
        return out;
    }

public:
    union
    {
        struct { KReal x, y, z; };

        KReal xyz[3];
    };
};

}