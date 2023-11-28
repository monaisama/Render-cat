#pragma once
#include <type_traits>

#include "compile_header.h"
#include "patterns.h"
#include "matrix.h"

namespace KMath
{

template<std::KReal TAngle = float>
class KRotator
{
public:
    K_API static const KRotator zero;

    GEN_DEFAULT_CONTRUCTOR_CODE_DEFAULT(KRotator)

public:
    KRotator(TAngle roll, TAngle pitch, TAngle yaw)
        : roll(roll), pitch(pitch), yaw(yaw) { }

    const TAngle& Yaw() const { return yaw; }
    const TAngle& Pitch() const { return pitch; }
    const TAngle& Roll() const { return roll; }

    template<std::KReal TReal = float>
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