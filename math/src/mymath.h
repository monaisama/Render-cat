#pragma once
#include "compile_header.h"
#include <cstdint>
#include <type_traits>
#include <cmath>
#include <cstdlib>
#include <exception>

namespace KMath
{

inline constexpr float epsilon = 1e-6;

inline constexpr float pi = 3.141593f;

template<class TFloat>
requires std::is_floating_point_v<TFloat>
inline TFloat Abs(TFloat number)
{
    return fabs(number);
}

template<class TInteger>
requires std::is_integral_v<TInteger> && (!std::is_same_v<TInteger, bool>)
inline TInteger Abs(TInteger number)
{
    return abs(number);
}

template<class TFloat>
requires std::is_floating_point_v<TFloat>
inline bool NearlyEquals(TFloat lhs, TFloat rhs, float error = epsilon)
{
    return Abs(lhs - rhs) < epsilon;
}

template<class TFloat>
requires std::is_floating_point_v<TFloat>
inline bool NearlyZero(TFloat lhs, float error = epsilon)
{
    return lhs < static_cast<TFloat>(epsilon);
}

template<class TNumber>
requires std::is_arithmetic_v<TNumber>
inline bool Equals(TNumber lhs, TNumber rhs)
{
    if constexpr (std::is_floating_point_v<TNumber>)
        return NearlyEquals(lhs, rhs);
    else if constexpr (std::is_integral_v<TNumber>)
        return lhs == rhs;
    else
        throw std::exception("not support type in mymath::Equals()");
}

template<class TNumber>
requires std::is_arithmetic_v<TNumber>
inline bool EqualsZero(TNumber lhs)
{
    if constexpr (std::is_floating_point_v<TNumber>)
        return NearlyZero(lhs);
    else if constexpr (std::is_integral_v<TNumber>)
        return lhs == 0;
    else
        throw std::exception("not support type in mymath::EqualsZero");
}

}