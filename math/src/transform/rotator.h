#pragma once
#include <type_traits>

#include "compile_header.h"
#include "matrix.h"

namespace KMath
{

template<class TAngle = float>
requires std::is_arithmetic_v<TAngle>
class KRotator
{
public:
    K_API static const KRotator zero;

    KRotator() = default;
    KRotator(TAngle roll, TAngle pitch, TAngle yaw)
        : roll(roll), pitch(pitch), yaw(yaw) { }
    KRotator(const KRotator&) = default;
    KRotator(KRotator&&) = default;
    KRotator& operator=(const KRotator&) = default;
    KRotator& operator=(KRotator&&) = default;

    const TAngle& Yaw() const { return yaw; }
    const TAngle& Pitch() const { return pitch; }
    const TAngle& Roll() const { return roll; }

    template<class TReal = float>
    requires std::is_arithmetic_v<TReal>
    KMatrix3x3<TReal> ToMatrix() const
    {
        return MakeRotateMatrix(KVec3<TReal>::up, yaw) *
        MakeRotateMatrix(KVec3<TReal>::right, pitch) *
        MakeRotateMatrix(KVec3<TReal>::forward, roll);
    }

protected:
    TAngle roll, pitch, yaw;
};

using KRotatorf = KRotator<float>;
using KRotatori = KRotator<int32_t>;

}