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

using KVec4f = KVec4<float>;
using KVec4i = KVec4<int32_t>;

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

template<class TReal, class TReal2 = TReal> requires std::is_arithmetic_v<TReal>
KVec3<TReal> ToVec3(const KVec4<TReal2>& vec4)
{
    // 这里需要齐次吗 todo.. 
    return KVec3<TReal> {
        static_cast<TReal>(vec4.X()),
        static_cast<TReal>(vec4.Y()),
        static_cast<TReal>(vec4.Z())
    };
}

template<class TReal, class TReal2 = TReal> requires std::is_arithmetic_v<TReal>
KVec3<TReal> ToVec2(const KVec3<TReal2>& vec3)
{
    return KVec2<TReal> {
        static_cast<TReal>(vec3.X()),
        static_cast<TReal>(vec3.Y())
    };
}

}