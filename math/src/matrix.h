#pragma once

#include "matrices/matrix2x2.h"
#include "matrices/matrix3x3.h"
#include "matrices/matrix4x4.h"
#include <cmath>
#include "mymath.h"

namespace KMath
{

using KMatrix2f = KMatrix2x2<float>;
using KMatrix2i = KMatrix2x2<int32_t>;

using KMatrix3f = KMatrix3x3<float>;
using KMatrix3i = KMatrix3x3<int32_t>;

using KMatrix4f = KMatrix4x4<float>;
using KMatrix4i = KMatrix4x4<int32_t>;

template<class TReal = float, class TReal2 = TReal>
requires std::is_arithmetic_v<TReal> && std::is_arithmetic_v<TReal2>
KVec2<TReal> operator*(const KVec2<TReal>& vec, const KMatrix2x2<TReal2>& matrix)
{
    return matrix * vec;
}
template<class TReal = float, class TReal2 = TReal>
requires std::is_arithmetic_v<TReal> && std::is_arithmetic_v<TReal2>
KVec2<TReal>& operator*=(KVec2<TReal>& vec, const KMatrix2x2<TReal2>& matrix)
{
    return vec = matrix * vec;
}

template<class TReal = float, class TReal2 = TReal>
requires std::is_arithmetic_v<TReal> && std::is_arithmetic_v<TReal2>
KVec3<TReal> operator*(const KVec3<TReal>& vec, const KMatrix3x3<TReal2>& matrix)
{
    return matrix * vec;
}
template<class TReal = float, class TReal2 = TReal>
requires std::is_arithmetic_v<TReal> && std::is_arithmetic_v<TReal2>
KVec3<TReal>& operator*=(KVec3<TReal>& vec, const KMatrix3x3<TReal2>& matrix)
{
    return vec = matrix * vec;
}
template<class TReal = float, class TReal2 = TReal>
requires std::is_arithmetic_v<TReal> && std::is_arithmetic_v<TReal2>
KVec4<TReal> operator*(const KVec4<TReal>& vec, const KMatrix4x4<TReal2>& matrix)
{
    return matrix * vec;
}
template<class TReal = float, class TReal2 = TReal>
requires std::is_arithmetic_v<TReal> && std::is_arithmetic_v<TReal2>
KVec4<TReal>& operator*=(const KVec4<TReal>& vec, const KMatrix4x4<TReal2>& matrix)
{
    return vec = matrix * vec;
}

// 构造出旋转任意角度的变换矩阵(angle是角度)
template<class TReal = float>
requires std::is_arithmetic_v<TReal>
KMatrix2x2<TReal> MakeRotateMatrix(float angle)
{
    angle *= degree2radian;
    TReal cosValue = static_cast<TReal>(cos(angle)), sinValue = static_cast<TReal>(sin(angle));
    return KMatrix2x2<TReal> {
        KVec2<TReal> { cosValue, sinValue },
        KVec2<TReal> { -sinValue, cosValue }
    };
}

// 构造出绕任意轴旋转的变换矩阵(angle是角度)
// 这里的所有向量都需要是单位向量，因为后面的公式都是用单位向量来推算出来的
template<class TReal = float, class TReal2 = TReal>
requires std::is_arithmetic_v<TReal> && std::is_arithmetic_v<TReal2>
KMatrix3x3<TReal> MakeRotateMatrix(KVec3<TReal2> vec, float angle)
{
    vec.Normalize();

    angle *= degree2radian;
    TReal cosValue = static_cast<TReal>(cos(angle)), sinValue = static_cast<TReal>(sin(angle));
    TReal i_cosValue = 1 - cosValue; // 1 - cos
    TReal nx = static_cast<TReal>(vec.X()), ny = static_cast<TReal>(vec.Y()), nz = static_cast<TReal>(vec.Z());
    TReal nx2 = nx * nx, ny2 = ny * ny, nz2 = nz * nz;
    TReal nxy = nx * ny, nxz = nx * nz, nyz = ny * nz;

    return KMatrix3x3<TReal> {
        KVec3<TReal> {
            nx2 * i_cosValue + cosValue,
            nxy * i_cosValue + nz * sinValue,
            nxz * i_cosValue - ny * sinValue
        },

        KVec3<TReal> {
            nxy * i_cosValue - nz * sinValue,
            ny2 * i_cosValue + cosValue,
            nyz * i_cosValue + nx * sinValue
        },

        KVec3<TReal> {
            nxz * i_cosValue + ny * sinValue,
            nyz * i_cosValue - nx * sinValue,
            nz2 * i_cosValue + cosValue
        }
    };
}

// 构造绕任意轴缩放的矩阵
// 这里的缩放轴是根据单位向量推算的
template<class TReal = float, class TReal2 = TReal, class TReal3 = TReal>
requires std::is_arithmetic_v<TReal> && std::is_arithmetic_v<TReal2> && std::is_arithmetic_v<TReal3>
KMatrix2x2<TReal> MakeScaleMatrix(KVec2<TReal2> vec, TReal3 scale)
{
    vec.Normalize();

    TReal nx2 = static_cast<TReal>(vec.X() * vec.X()), ny2 = static_cast<TReal>(vec.Y() * vec.Y());
    TReal nxy = static_cast<TReal>(vec.X() * vec.Y());
    TReal k_1 = static_cast<TReal>(scale - 1);

    return KMatrix2x2<TReal> {
        KVec2<TReal> { 1 + k_1 * nx2, k_1 * nxy },
        KVec2<TReal> { k_1 * nxy, 1 + k_1 * ny2 }
    };
}

template<class TReal = float, class TReal2 = TReal, class TReal3 = TReal>
requires std::is_arithmetic_v<TReal> && std::is_arithmetic_v<TReal2> && std::is_arithmetic_v<TReal3>
KMatrix3x3<TReal> MakeScaleMatrix(KVec3<TReal2> vec, TReal3 scale)
{
    vec.Normalize();

    TReal nx2 = static_cast<TReal>(vec.X() * vec.X()), ny2 = static_cast<TReal>(vec.Y() * vec.Y()), nz2 = static_cast<TReal>(vec.Z() * vec.Z());
    TReal nxy = static_cast<TReal>(vec.X() * vec.Y()), nxz = static_cast<TReal>(vec.X() * vec.Z()), nyz = static_cast<TReal>(vec.Y() * vec.Z());
    TReal k_1 = static_cast<TReal>(scale - 1);

    return KMatrix3x3<TReal> {
        KVec3<TReal> { 1 + k_1 * nx2, k_1 * nxy, k_1 * nxz },
        KVec3<TReal> { k_1 * nxy, 1 + k_1 * ny2, k_1 * nyz },
        KVec3<TReal> { k_1 * nxz, k_1*nyz, 1 + k_1 * nz2 },
    };
}

template<class TReal = float, class TReal2 = TReal>
requires std::is_arithmetic_v<TReal> && std::is_arithmetic_v<TReal2>
KMatrix4x4<TReal> MakeTranslateMatrix(KVec3<TReal2> vec)
{
    KMatrix4x4<TReal> ret = KMatrix4x4<TReal>::identity;
    ret[41] = static_cast<TReal>(vec.X());
    ret[42] = static_cast<TReal>(vec.Y());
    ret[43] = static_cast<TReal>(vec.Z());
    return ret;
}

}