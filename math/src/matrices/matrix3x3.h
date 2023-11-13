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
    template<class TValue> requires std::is_arithmetic_v<TValue>
    KMatrix3x3 operator/(TValue value) const { return operator*(1 / static_cast<TReal>(value)); }
    template<class TValue> requires std::is_arithmetic_v<TValue>
    KMatrix3x3& operator/=(TValue value) { return operator*=(1 / static_cast<TReal>(value)); }

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

    // 矩阵求逆 // 伴随矩阵除以行列式
    KMatrix3x3 Inverse() const { return Adjugete() / Det(); }
    // 行列式 // 任意选择一行或者一列的元素乘以对应的余子式矩阵的行列式
    // 3x3直接写公式
    TReal Det() const
    {
        return m11*m22*m33 + m12*m23* m31 + m13*m21*m32
            - m13*m22*m31 - m23*m32*m11 - m33*m12*m21;
    }
    // 是否是奇异矩阵
    bool IsSingular() const { return EqualsZero(Det()); }
    // 伴随矩阵 // 代数余子式矩阵的转置
    KMatrix3x3 Adjugete() const { return Cofactor().Transpose(); }
    // 余子式矩阵 // 代数余子式 = 有符号的余子式矩阵行列式
    KMatrix3x3 Cofactor() const
    {
        auto cofValue = [](TReal x1, TReal y1, TReal x2, TReal y2, int32_t indexSum)
        {
            TReal det = x1 * y2 - y1 * x2;
            return indexSum & 1 > 0 ? -det : det;
        };

        TReal cof11 = cofValue(m22, m23, m32, m33, 1 + 1);
        TReal cof12 = cofValue(m21, m23, m31, m33, 1 + 2);
        TReal cof13 = cofValue(m21, m22, m31, m32, 1 + 3);
        TReal cof21 = cofValue(m12, m13, m32, m33, 2 + 1);
        TReal cof22 = cofValue(m11, m13, m31, m33, 2 + 2);
        TReal cof23 = cofValue(m11, m12, m31, m32, 2 + 3);
        TReal cof31 = cofValue(m12, m13, m22, m23, 3 + 1);
        TReal cof32 = cofValue(m11, m13, m21, m23, 3 + 2);
        TReal cof33 = cofValue(m11, m12, m21, m22, 3 + 3);

        return KMatrix3x3 {
            KVec3<TReal> { cof11, cof12, cof13 },
            KVec3<TReal> { cof21, cof22, cof23 },
            KVec3<TReal> { cof31, cof32, cof33 }
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
