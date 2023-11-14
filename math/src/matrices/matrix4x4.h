#pragma once

#include "compile_header.h"
#include "vec.h"
#include <iostream>
#include "matrix3x3.h"
#include <type_traits>

namespace KMath
{

template<class TReal>
requires std::is_arithmetic_v<TReal>
class KMatrix4x4
{
public:
    K_API static const KMatrix4x4 identity;
    K_API static const KMatrix4x4 zero;

public:
    KMatrix4x4() = default;
    KMatrix4x4(const KVec4<TReal>& p, const KVec4<TReal>& q, const KVec4<TReal>& r, const KVec4<TReal>& w)
        : p(p), q(q), r(r), w(w) { }
    explicit KMatrix4x4(const KMatrix3x3<TReal>& mat3)
        : p(mat3.P()), q(mat3.Q()), r(mat3.R()), w(KVec3<TReal>::zero, 1)
    { }
    KMatrix4x4(const KMatrix4x4&) = default;
    KMatrix4x4(KMatrix4x4&&) = default;
    KMatrix4x4& operator=(const KMatrix4x4&) = default;
    KMatrix4x4& operator=(KMatrix4x4&&) = default;

    const KVec4<TReal>& P() const { return p; }
    const KVec4<TReal>& Q() const { return q; }
    const KVec4<TReal>& R() const { return r; }
    const KVec4<TReal>& W() const { return w; }

    const TReal* Matrix() const { return &matrix[0][0]; }

    TReal operator[](int32_t subIndex) const { return matrix[subIndex / 10 - 1][subIndex % 10 - 1]; }
    TReal& operator[](int32_t subIndex) { return matrix[subIndex / 10 - 1][subIndex % 10 - 1]; }

    template<class TValue> requires std::is_arithmetic_v<TValue>
    KMatrix4x4 operator*(TValue value) const
    {
        return KMatrix4x4 { p * value, q * value, r * value, w * value };
    }
    template<class TValue> requires std::is_arithmetic_v<TValue>
    KMatrix4x4& operator*=(TValue value)
    {
        p *= value; q *= value; r *= value; w *= value;
        return *this;
    }
    template<class TValue> requires std::is_arithmetic_v<TValue>
    KMatrix4x4 operator/(TValue value) const { return operator*(1 / static_cast<TReal>(value)); }
    template<class TValue> requires std::is_arithmetic_v<TValue>
    KMatrix4x4& operator/=(TValue value) { return operator*=(operator*(1 / static_cast<TReal>(value))); }

    KMatrix4x4 operator*(const KMatrix4x4& rhs) const
    {
        KMatrix4x4 ret;
        for (int32_t i = 0; i < 4; ++i)
        {
            for (int32_t j = 0; j < 4; ++j)
            {
                ret[i][j] = matrix[i][0] * rhs.matrix[0][j] +
                        matrix[i][1] * rhs.matrix[1][j] +
                        matrix[i][2] * rhs.matrix[2][j] +
                        matrix[i][3] * rhs.matrix[3][j];
            }
        }
        return ret;
    }
    KMatrix4x4& operator*=(const KMatrix4x4& rhs)
    {
        return *this = *this * rhs;
    }

    template<class TValue> requires std::is_arithmetic_v<TValue>
    KVec4<TValue> operator*(const KVec4<TValue>& rhs) const
    {
        return KVec4<TValue> {
            static_cast<TValue>(rhs.X() * m11 + rhs.Y() * m21 + rhs.Z() * m31 + rhs.W() * m41),
            static_cast<TValue>(rhs.X() * m12 + rhs.Y() * m22 + rhs.Z() * m32 + rhs.W() * m42),
            static_cast<TValue>(rhs.X() * m13 + rhs.Y() * m23 + rhs.Z() * m33 + rhs.W() * m43),
            static_cast<TValue>(rhs.X() * m14 + rhs.Y() * m24 + rhs.Z() * m34 + rhs.W() * m44)
        };
    }
    template<class TValue> requires std::is_arithmetic_v<TValue>
    KVec3<TValue> operator*(const KVec3<TValue>& rhs) const
    {
        return ToVec3<TValue>(operator*(KVec4<TValue>(rhs, 1)));
    }
    template<class TValue> requires std::is_arithmetic_v<TValue>
    KVec4<TValue> TransformVector(const KVec4<TValue>& rhs) const { return *this * rhs; }
    template<class TValue> requires std::is_arithmetic_v<TValue>
    KVec3<TValue> TransformVector(const KVec3<TValue>& rhs) const { return *this * rhs; }

    // 转置
    KMatrix4x4 Transpose() const
    {
        return KMatrix4x4 {
            KVec4<TReal> { m11, m21, m31, m41 },
            KVec4<TReal> { m12, m22, m32, m42 },
            KVec4<TReal> { m13, m23, m33, m43 },
            KVec4<TReal> { m14, m24, m34, m44 }
        };
    }

    // 逆 // 伴随矩阵除以行列式
    KMatrix4x4 Inverse() const
    {
        return Adjugate() / Det();
    }

    // 余子式矩阵
    KMatrix4x4 CofactorMatrix() const
    {
        KMatrix4x4 cofMatrix;

        cofMatrix.m11 = CofactorValue(m22, m23, m24, m32, m33, m34, m42, m43, m44, 1+1);
        cofMatrix.m12 = CofactorValue(m21, m23, m24, m31, m33, m34, m41, m43, m44, 1+2);
        cofMatrix.m13 = CofactorValue(m21, m22, m24, m31, m32, m34, m41, m42, m44, 1+3);
        cofMatrix.m14 = CofactorValue(m21, m22, m23, m31, m32, m33, m41, m42, m43, 1+4);

        cofMatrix.m21 = CofactorValue(m12, m13, m14, m32, m33, m34, m42, m43, m44, 2+1);
        cofMatrix.m22 = CofactorValue(m11, m13, m14, m31, m33, m34, m41, m43, m44, 2+2);
        cofMatrix.m23 = CofactorValue(m11, m12, m14, m31, m32, m34, m41, m42, m44, 2+3);
        cofMatrix.m24 = CofactorValue(m11, m12, m13, m31, m32, m33, m41, m42, m43, 2+4);
        
        cofMatrix.m31 = CofactorValue(m12, m13, m14, m22, m23, m24, m42, m43, m44, 3+1);
        cofMatrix.m32 = CofactorValue(m11, m13, m14, m21, m23, m24, m41, m43, m44, 3+2);
        cofMatrix.m33 = CofactorValue(m11, m12, m14, m21, m22, m24, m41, m42, m44, 3+3);
        cofMatrix.m34 = CofactorValue(m11, m12, m13, m21, m22, m23, m41, m42, m43, 3+4);
        
        cofMatrix.m41 = CofactorValue(m12, m13, m14, m22, m23, m24, m32, m33, m34, 4+1);
        cofMatrix.m42 = CofactorValue(m11, m13, m14, m21, m23, m24, m31, m33, m34, 4+2);
        cofMatrix.m43 = CofactorValue(m11, m12, m14, m21, m22, m24, m31, m32, m34, 4+3);
        cofMatrix.m44 = CofactorValue(m11, m12, m13, m21, m22, m23, m31, m32, m33, 4+4);

        return cofMatrix;
    }

    // 行列式 // 任选一行或者一列求代数余子式和此元素的乘积的和
    TReal Det() const
    {
        // 这里随便选定第一行
        return m11 * CofactorValue(m22, m23, m24, m32, m33, m34, m42, m43, m44, 1+1) +
            m12 * CofactorValue(m21, m23, m24, m31, m33, m34, m41, m43, m44, 1+2) +
            m13 * CofactorValue(m21, m22, m24, m31, m32, m34, m41, m42, m44, 1+3) +
            m14 * CofactorValue(m21, m22, m23, m31, m32, m33, m41, m42, m43, 1+4);
    }

    // 伴随矩阵 // 代数余子式矩阵的转置
    KMatrix4x4 Adjugate() const
    {
        return CofactorMatrix().Transpose();
    }

protected:
    friend std::ostream& operator<<(std::ostream& out, const KMatrix4x4& rhs)
    {
        out << rhs.p << "\n";
        out << rhs.q << "\n";
        out << rhs.r << "\n";
        out << rhs.w << "\n";
        return out;
    }

    TReal CofactorValue(TReal x1, TReal y1, TReal z1,
        TReal x2, TReal y2, TReal z2,
        TReal x3, TReal y3, TReal z3,
        int32_t sumIndex) const
    {
        // 有符号行列式
        TReal cofValue = KMatrix3x3<TReal> {
            KVec3<TReal> {x1, y1, z1},
            KVec3<TReal> {x2, y2, z2},
            KVec3<TReal> {x3, y3, z3}
        }.Det(); // 行列式
        return (sumIndex % 2 == 0) ? cofValue : -cofValue;
    }

protected:
    union
    {
        struct
        {
            TReal m11, m12, m13, m14;
            TReal m21, m22, m23, m24;
            TReal m31, m32, m33, m34;
            TReal m41, m42, m43, m44;
        };

        struct { KVec4<TReal> p, q, r, w; };

        TReal matrix[4][4];
    };
};

}
