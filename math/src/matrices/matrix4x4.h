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
            static_cast<TValue>(rhs.X() * m11 + rhs.Y() * m21 + rhs.Z() * m31, rhs.W() * m41),
            static_cast<TValue>(rhs.X() * m12 + rhs.Y() * m22 + rhs.Z() * m32, rhs.W() * m42),
            static_cast<TValue>(rhs.X() * m13 + rhs.Y() * m23 + rhs.Z() * m33, rhs.W() * m43),
            static_cast<TValue>(rhs.X() * m14 + rhs.Y() * m24 + rhs.Z() * m34, rhs.W() * m44),
        };
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
