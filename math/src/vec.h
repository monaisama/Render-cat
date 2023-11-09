#pragma once

#include "vecs/vec2.h"
#include "vecs/vec3.h"
#include "vecs/vec4.h"

namespace KMath
{

using KVec2f = KVec2<float>;
using KVec2i = KVec2<int32_t>;

using KVec3f = KVec3<float>;
using KVec3i = KVec3<int32_t>;

template<class TReal> requires std::is_arithmetic_v<TReal>
float Distance(const KVec2<TReal>& lhs, const KVec2<TReal>& rhs)
{
    return (lhs - rhs).Length();
}

template<class TReal> requires std::is_arithmetic_v<TReal>
float Distance(const KVec3<TReal>& lhs, const KVec3<TReal>& rhs)
{
    return (lhs - rhs).Length();
}

}