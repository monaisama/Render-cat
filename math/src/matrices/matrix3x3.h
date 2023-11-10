#pragma once

#include "compile_header.h"
#include "vec.h"
#include <iostream>

namespace KMath
{

// 矩阵使用行向量，也就是说需要向量左乘矩阵来变换
template<class TReal>
requires std::is_arithmetic_v<TReal>
class KMatrix3x3
{
public:
    K_API static const KMatrix3x3 identity;
    K_API static const KMatrix3x3 zero;

public:
    KMatrix3x3() = default;
    KMatrix3x3(const KVec3<TReal>& p, const KVec3<TReal>& q, const KVec3<TReal>& r)
        : p (p), q(q), r(r)
    { }
    KMatrix3x3(const KMatrix3x3&) = default;
    KMatrix3x3(KMatrix3x3&&) = default;
    KMatrix3x3& operator=(const KMatrix3x3&) = default;
    KMatrix3x3& operator=(KMatrix3x3&&) = default;

    template<class TValue> requires std::is_arithmetic_v<TValue>
    KMatrix3x3 operator*(TValue value) const { return KMatrix3x3 { p * value, q * value, r * value }; }
    template<class TValue> requires std::is_arithmetic_v<TValue>
    KMatrix3x3& operator*=(TValue value)
    {
        p *= value; q *= value; r *= value;
        return *this;
    }

    KMatrix3x3 operator*(const KMatrix3x3& rhs) const
    {
        KMatrix3x3 ret;
        for (int32_t i = 0; i < 3; ++i)
        {
            for (int32_t j = 0; j < 3; ++j)
            {
                // row i coll j
                ret.matrix[i][j] =
                    matrix[i][0] * rhs.matrix[0][j] +
                    matrix[i][1] * rhs.matrix[1][j] +
                    matrix[i][2] * rhs.matrix[2][j];
            }
        }
        return ret;
    }
    KMatrix3x3& operator*=(const KMatrix3x3& rhs) { return *this = *this * rhs; }

    // 左乘一个变换的向量（变换到矩阵代表的空间中）
    template<class TValue = TReal> requires std::is_arithmetic_v<TValue>
    KVec3<TValue> operator*(const KVec3<TValue>& rhs) const
    {
        return KVec3<TValue> {
            static_cast<TValue>(rhs.X() * m11 + rhs.Y() * m21 + rhs.Z() * m31),
            static_cast<TValue>(rhs.X() * m12 + rhs.Y() * m22 + rhs.Z() * m32),
            static_cast<TValue>(rhs.X() * m13 + rhs.Y() * m23 + rhs.Z() * m33)
        };
    }

    template<class TValue = TReal> requires std::is_arithmetic_v<TValue>
    KVec3<TValue> TransformVector(const KVec3<TValue>& vec) const
    {
        return *this * vec;
    }

    // 转置
    KMatrix3x3 Transpose() const
    {
        return KMatrix3x3 {
            KVec3<TReal> { m11, m21, m31 },
            KVec3<TReal> { m12, m22, m32 },
            KVec3<TReal> { m13, m23, m33 }
        };
    }

protected:
    friend std::ostream& operator<<(std::ostream& out, const KMatrix3x3& rhs)
    {
        out << rhs.p << "\n";
        out << rhs.q << "\n";
        out << rhs.r << "\n";
        return out;
    }

protected:
    union
    {
        struct
        {
            TReal m11, m12, m13;
            TReal m21, m22, m23;
            TReal m31, m32, m33;
        };

        struct
        {
            KVec3<TReal> p, q, r;
        };

        TReal matrix[3][3];
    };
};

}
