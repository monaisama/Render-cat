#pragma once
#include "compile_header.h"
#include "vec.h"
#include <iostream>

namespace KMath
{

// 行向量
template<class TReal>
requires std::is_arithmetic_v<TReal>
class KMatrix2x2
{
public:
    K_API static const KMatrix2x2 identity;
    K_API static const KMatrix2x2 zero;

public:
    KMatrix2x2() = default;
    KMatrix2x2(const KVec2<TReal>& p, const KVec2<TReal>& q) : p(p), q(q) { }
    KMatrix2x2(const KMatrix2x2&) = default;
    KMatrix2x2(KMatrix2x2&&) = default;
    KMatrix2x2& operator=(const KMatrix2x2&) = default;
    KMatrix2x2& operator=(KMatrix2x2&&) = default;

    KMatrix2x2 operator*(const KMatrix2x2& rhs) const
    {
        KMatrix2x2 ret;
        ret.m11 = m11 * rhs.m11 + m12 * rhs.m21;
        ret.m12 = m11 * rhs.m12 + m12 * rhs.m22;
        ret.m21 = m21 * rhs.m11 + m22 * rhs.m21;
        ret.m22 = m21 * rhs.m12 + m22 * rhs.m22;
        return ret;
    }
    KMatrix2x2& operator*=(const KMatrix2x2& rhs)
    {
        return *this = *this * rhs;
    }

    template<class TValue> requires std::is_arithmetic_v<TValue>
    KMatrix2x2 operator*(TValue value) const { return KMatrix2x2 { p * value, q * value }; }
    template<class TValue> requires std::is_arithmetic_v<TValue>
    KMatrix2x2& operator*=(TValue value) { return *this = *this * value; }
    template<class TValue = TReal> requires std::is_arithmetic_v<TValue>
    KVec2<TValue> operator*(const KVec2<TValue>& rhs) const
    {
        return KVec2<TValue> {
            static_cast<TValue>(rhs.X() * m11 + rhs.Y() * m21),
            static_cast<TValue>(rhs.X() * m12 + rhs.Y() * m22)
        };
    }
    template<class TValue> requires std::is_arithmetic_v<TValue>
    KMatrix2x2 operator/(TValue value) const { return operator*(1 / static_cast<TReal>(value)); }
    template<class TValue> requires std::is_arithmetic_v<TValue>
    KMatrix2x2& operator/=(TValue value) { return operator*=(1 / static_cast<TReal>(value)); }

    template<class TValue = TReal> requires std::is_arithmetic_v<TValue>
    KVec2<TValue> TransformVector(const KVec2<TValue>& vec) const
    {
        return *this * vec;
    }

    // 矩阵转置
    KMatrix2x2 Transpose() const
    {
        return KMatrix2x2 {
            KVec2<TReal> { m11, m21 },
            KVec2<TReal> { m12, m22 }
        };
    }

    // 计算出2x2矩阵的行列式
    TReal Det() const { return m11 * m22 - m12 * m21; }
    // 计算是否是奇异矩阵
    bool IsSingular() const { return EqualsZero(Det()); } // 行列式为0

    // 矩阵求逆 // 需要确保这里不是奇异矩阵 // 这里假定一定是正交矩阵吗？还是说一定用伴随矩阵求解
    // 施密特正交化 todo..
    // 逆矩阵是伴随矩阵除以行列式
    KMatrix2x2 Inverse() const { return Adjugate() / Det(); }
    // 代数余子式矩阵
    KMatrix2x2 Cofactor() const
    {
        KMatrix2x2 cof;
        {
            cof.m11 = m22;
            cof.m12 = -m21;
            cof.m21 = -m12;
            cof.m22 = m11;
        }
        return cof;
    }
    // 伴随矩阵是代数余子式矩阵的转置矩阵
    KMatrix2x2 Adjugate() const { return Cofactor().Transpose(); }

protected:
    friend std::ostream& operator<<(std::ostream& out, const KMatrix2x2& rhs)
    {
        out << rhs.p << "\n";
        out << rhs.q << "\n";
        return out;
    }
    
protected:
    union
    {
        struct
        {
            TReal m11, m12;
            TReal m21, m22;
        };

        struct { KVec2<TReal> p, q; };

        TReal matrix[2][2];
    };
};

}