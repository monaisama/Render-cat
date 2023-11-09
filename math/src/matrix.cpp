#include "matrix.h"
#include "vec.h"

namespace KMath
{

const KMatrix3f KMatrix3f::identity { KVec3f::forward, KVec3f::right, KVec3f::up };
const KMatrix3f KMatrix3f::zero {};

const KMatrix3i KMatrix3i::identity { KVec3i::forward, KVec3i::right, KVec3i::up };
const KMatrix3i KMatrix3i::zero {};

const KMatrix2f KMatrix2f::identity { KVec2f::right, KVec2f::up };
const KMatrix2f KMatrix2f::zero {};

const KMatrix2i KMatrix2i::identity { KVec2i::right, KVec2i::up };
const KMatrix2i KMatrix2i::zero {};

}