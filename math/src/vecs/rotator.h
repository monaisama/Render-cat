#pragma once
#include <type_traits>

namespace KMath
{

template<class TAngle>
requires std::is_arithmetic_v<TAngle>
class KRotator
{
public:
    KRotator() = default;
    KRotator(TAngle roll, TAngle pitch, TAngle yaw)
        : roll(roll), pitch(pitch), yaw(yaw) { }
    KRotator(const KRotator&) = default;
    KRotator(KRotator&&) = default;
    KRotator& operator=(const KRotator&) = default;
    KRotator& operator=(KRotator&&) = default;

protected:
    TAngle roll, pitch, yaw;
};

}