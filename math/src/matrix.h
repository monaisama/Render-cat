#pragma once

#include "matrices/matrix3x3.h"
#include "matrices/matrix2x2.h"
#include <cmath>
#include "mymath.h"

namespace KMath
{

using KMatrix3f = KMatrix3x3<float>;
using KMatrix3i = KMatrix3x3<int32_t>;

using KMatrix2f = KMatrix2x2<float>;
using KMatrix2i = KMatrix2x2<int32_t>;

// 构造出旋转任意角度的变换矩阵(angle是角度)
template<class TReal>
KMatrix2x2<TReal> MakeRotateMatrix(float angle)
{
    angle *= degree2radian;
    float cosValue = cos(angle), sinValue = sin(angle);
    return KMatrix2x2 {
        KVec2<TReal> { cosValue, sinValue },
        KVec2<TReal> { -sinValue, cosValue }
    };
}

// 构造出绕任意轴旋转的变换矩阵(angle是角度)
template<class TReal, class TReal2 = TReal>
KMatrix3x3<TReal> MakeRotateMatrix(KVec3<TReal2> vec, float angle)
{
    angle *= degree2radian;
    float cosValue = cos(angle), sinValue = sin(angle);
    float i_cosValue = 1.f - cosValue; // 1 - cos
    float nx = vec.X(), ny = vec.Y(), nz = vec.Z();
    float nx2 = nx * nx, ny2 = ny * ny, nz2 = nz * nz;
    float nxy = nx * ny, nxz = nx * nz, nyz = ny * nz;

    return KMatrix3x3 {
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

}