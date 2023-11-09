#include "vec.h"

namespace KMath
{

const KVec2f KVec2f::up { 0.f, 1.f };
const KVec2f KVec2f::right { 1.f, 0.f };
const KVec2f KVec2f::zero { 0.f, 0.f };

const KVec2i KVec2i::up { 0, 1 };
const KVec2i KVec2i::right { 1, 0 };
const KVec2i KVec2i::zero { 0, 0 };

const KVec3f KVec3f::up { 0.f, 0.f, 1.f };
const KVec3f KVec3f::right { 0.f, 1.f, 0.f };
const KVec3f KVec3f::forward { 1.f, 0.f, 0.f };

const KVec3i KVec3i::up { 0, 0, 1 };
const KVec3i KVec3i::right { 0, 1, 0 };
const KVec3i KVec3i::forward { 1, 0, 0 };

}