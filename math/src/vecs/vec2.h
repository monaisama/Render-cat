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

    const KReal* XY() { return xy; }

    KVec2 operator+(const KVec2& rhs) { return KVec2 { x + rhs.x, y + rhs.y }; }
    KVec2& operator+=(const KVec2& rhs) { x += rhs.x; y += rhs.y; return *this; }
    
    KVec2 operator-(const KVec2& rhs) { return KVec2 { x - rhs.x, y - rhs.y }; }
    KVec2& operator-=(const KVec2& rhs) { x -= rhs.x; y -= rhs.y; return *this; }

    KVec2& operator-() { return *this *= -1; }

    template<class TValue> requires std::is_arithmetic_v<TValue>
    KVec2 operator*(TValue v)
    {
        KReal value = static_cast<KReal>(v);
        return KVec2 { value * x, value * y };
    }
    template<class TValue> requires std::is_arithmetic_v<TValue>
    KVec2& operator*=(TValue v)
    {
        KReal value = static_cast<KReal>(v);
        x *= value;
        y *= value;
        return *this;
    }

    template<class TValue> requires std::is_arithmetic_v<TValue>
    KVec2 operator/(TValue v)
    {
        KReal value = static_cast<KReal>(v);
        if (KMath::EqualsZero(value))
        {
            KLog::LogSimpleError("divide zero error.");
            return KVec2::zero;
        }
        return *this * (1 / value);
    }
    template<class TValue> requires std::is_arithmetic_v<TValue>
    KVec2& operator/=(TValue v)
    {
        KReal value = static_cast<KReal>(v);
        if (KMath::EqualsZero(value))
        {
            KLog::LogSimpleError("divide zero error.");
            return *this;
        }
        return *this *= (1 / value);
    }

    bool operator==(const KVec2& rhs) { return KMath::Equals(x, rhs.x) && KMath::Equals(y, rhs.y); }
    bool operator!=(const KVec2& rhs) { return !(*this == rhs); }

    // 点乘
    float operator|(const KVec2& rhs) { return static_cast<float>(x * rhs.x, y * rhs.y); }
    static float Dot(const KVec2& lhs, const KVec2& rhs) { return lhs | rhs; }

    // 叉乘
    /*[x1, y1] X [x2, y2] = ([x1, 0] + [0, y1]) X ([x2, 0] + [0, y2])
    * 用分配率并且用轴来表现(i, j, k ... 来表示坐标轴的单位向量) 计算之后就是
    * x1_i X x2_i + x1_i X y2_j + y1_j X x2_i + y1_j X y2_j
    * 再根据 和标量的结合律 还有 i X i = 0 i X j = k j X i = -k (二维中也是垂直于ij,但是无法表示，可用于判定)
    * 0 + x1y2_k - y1x2_k + 0
    * 得到 [x1y2, -y1x2]
    */
    KVec2 operator^(const KVec2& rhs) { return KVec2 { x * rhs.y, -y * rhs.x}; }
    static KVec2 Cross(const KVec2& lhs, const KVec2& rhs) { return lhs ^ rhs; }

    KVec2& Normalize()
    {
        if constexpr (std::is_integral_v<KReal>)
        {
            KLog::LogSimpleWarning("maybe loss of precision warning.");
        }
        float length = Length();
        if (KMath::NearlyZero(length))
            return *this;
        return *this /= length;
    }

    float Length()
    {
        return sqrt(static_cast<float>(SqrtLength()));
    }

    KReal SqrtLength()
    {
        return x * x + y * y;
    }

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
