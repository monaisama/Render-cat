#pragma once

#include "vec.h"
#include "rotator.h"

namespace KMath
{

template<class TReal = float, class TVec = KVec3<TReal>, class TRotator = KRotator<TReal>>
requires std::is_arithmetic_v<TReal>
class KTransform
{
public:
    KTransform() : location(), rotation(), scale(TVec::one) { }
    KTransform(const TVec& location, const TRotator& rotation, const TVec& scale)
        : location(location), rotation(rotation), scale(scale) { }
    KTransform(const KTransform&) = default;
    KTransform(KTransform&&) = default;
    KTransform& operator=(const KTransform&) = default;
    KTransform& operator=(KTransform&&) = default;
    
    const TVec& GetLocation() const { return location; }
    const TRotator& GetRotation() const { return rotation; }
    const TVec& GetScale() const { return scale; }

protected:
    TVec location;
    TRotator rotation;
    TVec scale;
};

using KTransform2f = KTransform<float, KVec2f, float>;
using KTransform2i = KTransform<int32_t, KVec2i, int32_t>;

using KTransform3f = KTransform<float, KVec3f, KRotatorf>;
using KTransform3i = KTransform<int32_t, KVec3i, KRotatori>;

}