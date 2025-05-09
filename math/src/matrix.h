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

template<std::KReal TReal = float, std::KReal TReal2 = TReal>
KVec2<TReal> operator*(const KVec2<TReal>& vec, const KMatrix2x2<TReal2>& matrix)
{
    return matrix * vec;
}
template<std::KReal TReal = float, std::KReal TReal2 = TReal>
KVec2<TReal>& operator*=(KVec2<TReal>& vec, const KMatrix2x2<TReal2>& matrix)
{
    return vec = matrix * vec;
}

template<std::KReal TReal = float, std::KReal TReal2 = TReal>
KVec2<TReal> operator*(const KVec2<TReal>& vec, const KMatrix3x3<TReal2>& matrix)
{
    return matrix * vec;
}
template<std::KReal TReal = float, std::KReal TReal2 = TReal>
KVec2<TReal>& operator*=(KVec2<TReal>& vec, const KMatrix3x3<TReal2>& matrix)
{
    return vec = matrix * vec;
}

template<std::KReal TReal = float, std::KReal TReal2 = TReal>
KVec3<TReal> operator*(const KVec3<TReal>& vec, const KMatrix3x3<TReal2>& matrix)
{
    return matrix * vec;
}
template<std::KReal TReal = float, std::KReal TReal2 = TReal>
KVec3<TReal>& operator*=(KVec3<TReal>& vec, const KMatrix3x3<TReal2>& matrix)
{
    return vec = matrix * vec;
}

template<std::KReal TReal = float, std::KReal TReal2 = TReal>
KVec3<TReal> operator*(const KVec3<TReal>& vec, const KMatrix4x4<TReal2>& matrix)
{
    return matrix * vec;
}
template<std::KReal TReal = float, std::KReal TReal2 = TReal>
KVec3<TReal>& operator*=(KVec3<TReal>& vec, const KMatrix4x4<TReal2>& matrix)
{
    return vec = matrix * vec;
}

template<std::KReal TReal = float, std::KReal TReal2 = TReal>
KVec4<TReal> operator*(const KVec4<TReal>& vec, const KMatrix4x4<TReal2>& matrix)
{
    return matrix * vec;
}

template<std::KReal TReal = float, std::KReal TReal2 = TReal>
KVec4<TReal>& operator*=(const KVec4<TReal>& vec, const KMatrix4x4<TReal2>& matrix)
{
    return vec = matrix * vec;
}

// �������ת����Ƕȵı任����(angle�ǽǶ�)
template<std::KReal TReal = float, std::KReal TReal2 = TReal>
KMatrix2x2<TReal> MakeRotateMatrix(TReal2 angle)
{
    angle = static_cast<TReal2>(Radians(angle));
    TReal cosValue = static_cast<TReal>(cos(angle)), sinValue = static_cast<TReal>(sin(angle));
    return KMatrix2x2<TReal> {
        KVec2<TReal> { cosValue, sinValue },
        KVec2<TReal> { -sinValue, cosValue }
    };
}

// ���������������ת�ı任����(angle�ǽǶ�)
// �����������������Ҫ�ǵ�λ��������Ϊ����Ĺ�ʽ�����õ�λ���������������
template<std::KReal TReal = float, std::KReal TReal2 = TReal, std::KReal TReal3 = float>
KMatrix3x3<TReal> MakeRotateMatrix(const KVec3<TReal2>& vec, TReal3 angle)
{
    const_cast<KVec3<TReal2>&>(vec).Normalize();

    angle = static_cast<TReal3>(Radians(angle));
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

// ���������������ŵľ���
// ������������Ǹ��ݵ�λ���������
template<std::KReal TReal = float, std::KReal TReal2 = TReal, std::KReal TReal3 = float>
KMatrix2x2<TReal> MakeScaleMatrix(const KVec2<TReal2>& vec, TReal3 scale)
{
    const_cast<KVec2<TReal2>&>(vec).Normalize();

    TReal nx2 = static_cast<TReal>(vec.X() * vec.X()), ny2 = static_cast<TReal>(vec.Y() * vec.Y());
    TReal nxy = static_cast<TReal>(vec.X() * vec.Y());
    TReal k_1 = static_cast<TReal>(scale - 1);

    return KMatrix2x2<TReal> {
        KVec2<TReal> { 1 + k_1 * nx2, k_1 * nxy },
        KVec2<TReal> { k_1 * nxy, 1 + k_1 * ny2 }
    };
}

template<std::KReal TReal = float, std::KReal TReal2 = TReal, std::KReal TReal3 = float>
KMatrix3x3<TReal> MakeScaleMatrix(const KVec3<TReal2>& vec, TReal3 scale)
{
    const_cast<KVec3<TReal2>&>(vec).Normalize();

    TReal nx2 = static_cast<TReal>(vec.X() * vec.X()), ny2 = static_cast<TReal>(vec.Y() * vec.Y()), nz2 = static_cast<TReal>(vec.Z() * vec.Z());
    TReal nxy = static_cast<TReal>(vec.X() * vec.Y()), nxz = static_cast<TReal>(vec.X() * vec.Z()), nyz = static_cast<TReal>(vec.Y() * vec.Z());
    TReal k_1 = static_cast<TReal>(scale - 1);

    return KMatrix3x3<TReal> {
        KVec3<TReal> { 1 + k_1 * nx2, k_1 * nxy, k_1 * nxz },
        KVec3<TReal> { k_1 * nxy, 1 + k_1 * ny2, k_1 * nyz },
        KVec3<TReal> { k_1 * nxz, k_1*nyz, 1 + k_1 * nz2 },
    };
}

template<std::KReal TReal = float, std::KReal TReal2 = TReal>
KMatrix3x3<TReal> MakeScaleMatrix(const KVec3<TReal2>& scale)
{
    return KMatrix3x3<TReal> {
        KVec3<TReal> { static_cast<TReal>(scale.X()), 0, 0 },
        KVec3<TReal> { 0, static_cast<TReal>(scale.Y()), 0 },
        KVec3<TReal> { 0, 0, static_cast<TReal>(scale.Z()) }
    };
}

template<std::KReal TReal = float, std::KReal TReal2 = TReal>
KMatrix2x2<TReal> MakeScaleMatrix(const KVec2<TReal2>& scale)
{
    return KMatrix2x2<TReal> {
        KVec2<TReal> { static_cast<TReal>(scale.X()), 0 },
        KVec2<TReal> { 0, static_cast<TReal>(scale.Y()) }
    };
}

template<std::KReal TReal = float, std::KReal TReal2 = TReal>
KMatrix3x3<TReal> MakeTranslateMatrix(const KVec2<TReal2>& vec)
{
    KMatrix3x3<TReal> ret(KMatrix3x3<TReal>::identity);
    ret[31] = static_cast<TReal>(vec.X());
    ret[32] = static_cast<TReal>(vec.Y());
    return ret;
}

template<std::KReal TReal = float, std::KReal TReal2 = TReal>
KMatrix4x4<TReal> MakeTranslateMatrix(const KVec3<TReal2>& vec)
{
    KMatrix4x4<TReal> ret(KMatrix4x4<TReal>::identity);
    ret[41] = static_cast<TReal>(vec.X());
    ret[42] = static_cast<TReal>(vec.Y());
    ret[43] = static_cast<TReal>(vec.Z());
    return ret;
}

template<std::KReal TReal = float>
KMatrix4x4<TReal> ToMatrix4(const KMatrix3x3<TReal>& mat)
{
    return KMatrix4x4<TReal> {
        mat
    };
}

template<std::KReal TReal = float>
KMatrix3x3<TReal> ToMatrix3(const KMatrix3x3<TReal>& mat)
{
    return KMatrix3x3<TReal> {
        mat
    };
}

template<std::KReal TReal = float>
KMatrix4x4<TReal> LookAt(const KVec3<TReal>& location, const KVec3<TReal>& target)
{
    auto forward = target - location;
    forward.Normalize();

    auto right = KVec3<TReal>::Cross(KVec3<TReal>::up, forward);
    auto up = KVec3<TReal>::Cross(forward, right);

    return KMatrix4x4<TReal> {
        KVec4<TReal> { forward },
        KVec4<TReal> { right },
        KVec4<TReal> { up },
        KVec4<TReal>::wzero
    } * MakeTranslateMatrix(location);
}

}