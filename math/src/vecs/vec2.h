#pragma once

#include "mymath.h"
#include "log.h"
#include <type_traits>
#include <iostream>

namespace KMath
{

template<class TELE>
requires std::is_arithmetic_v<TELE>
class KVec2
{
    using KReal = TELE;
public:
    K_API static const KVec2 up;
    K_API static const KVec2 right;
    K_API static const KVec2 zero;

public:
    KVec2() = default;
    KVec2(KReal x, KReal y) : x(x), y(y) { }
    KVec2(const KVec2&) = default;
    KVec2(KVec2&&) = default;
    KVec2& operator=(const KVec2&) = default;
    KVec2& operator=(KVec2&&) = default;

    const KReal& X() const { return x; }
    const KReal& Y() const { return y; }

    KReal& X() { return x; }
    KReal& Y() { return y; }

    const KReal* XY() const { return xy; }

    KVec2 operator+(const KVec2& rhs) const { return KVec2 { x + rhs.x, y + rhs.y }; }
    KVec2& operator+=(const KVec2& rhs) { x += rhs.x; y += rhs.y; return *this; }
    
    KVec2 operator-(const KVec2& rhs) const { return KVec2 { x - rhs.x, y - rhs.y }; }
    KVec2& operator-=(const KVec2& rhs) { x -= rhs.x; y -= rhs.y; return *this; }

    KVec2& operator-() { return *this *= -1; }

    template<class TValue> requires std::is_arithmetic_v<TValue>
    KVec2 operator*(TValue value) const
    {
        return KVec2 { static_cast<KReal>(value * x), static_cast<KReal>(value * y) };
    }
    template<class TValue> requires std::is_arithmetic_v<TValue>
    KVec2& operator*=(TValue value)
    {
        x = static_cast<KReal>(x * value);
        y = static_cast<KReal>(y * value);
        return *this;
    }

    template<class TValue> requires std::is_arithmetic_v<TValue>
    KVec2 operator/(TValue value) const
    {
        if (EqualsZero(value))
        {
            KLog::LogSimpleError("divide zero error.");
            return *this;
        }
        return KVec2 { static_cast<KReal>(x / value), static_cast<KReal>(y / value) };
    }
    template<class TValue> requires std::is_arithmetic_v<TValue>
    KVec2& operator/=(TValue value)
    {
        if (EqualsZero(value))
        {
            KLog::LogSimpleError("divide zero error.");
            return *this;
        }
        x = static_cast<KReal>(x / value);
        y = static_cast<KReal>(y / value);
        return *this;
    }

    bool operator==(const KVec2& rhs) const { return Equals(x, rhs.x) && Equals(y, rhs.y); }
    bool operator!=(const KVec2& rhs) const { return !(*this == rhs); }

    // 点乘
    KReal operator|(const KVec2& rhs) const { return x * rhs.x + y * rhs.y; }
    static KReal Dot(const KVec2& lhs, const KVec2& rhs) { return lhs | rhs; }

    // 叉乘
    /*[x1, y1] X [x2, y2] = ([x1, 0] + [0, y1]) X ([x2, 0] + [0, y2])
    * 用分配率并且用轴来表现(i, j, k ... 来表示坐标轴的单位向量) 计算之后就是
    * x1_i X x2_i + x1_i X y2_j + y1_j X x2_i + y1_j X y2_j
    * 再根据 和标量的结合律 还有 i X i = 0 i X j = k j X i = -k (二维中也是垂直于ij,但是无法表示，可用于判定)
    * 0 + x1y2_k - y1x2_k + 0
    * 得到 [x1y2, -y1x2]
    */
    KVec2 operator^(const KVec2& rhs) const { return KVec2 { x * rhs.y, -y * rhs.x}; }
    static KVec2 Cross(const KVec2& lhs, const KVec2& rhs) { return lhs ^ rhs; }

    KVec2& Normalize()
    {
        if constexpr (std::is_integral_v<KReal>)
        {
            KLog::LogSimpleWarning("maybe loss of precision warning.");
        }
        float length = Length();
        if (NearlyZero(length))
            return *this;
        return *this /= length;
    }

    float Length() const { return sqrt(static_cast<float>(SqrtLength())); }
    KReal SqrtLength() const { return x * x + y * y; }

protected:
    friend std::ostream& operator<<(std::ostream& out, const KVec2& rhs)
    {
        out << "{ " << rhs.x << ", " << rhs.y << " }";
        return out;
    }

protected:
    union
    {
        struct { KReal x, y; };

        KReal xy[2];
    };
};

}
