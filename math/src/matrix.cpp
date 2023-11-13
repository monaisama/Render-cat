#include "matrix.h"
#include "vec.h"

namespace KMath
{

/* ill-format 这里 dynamic-initialization顺序不确定，所以可能forward可能还没有初始化完毕
* 1, 将 right forward 这些写在对应vec的template 的.h 文件中 不导出，这样的话就可以每一个编译单元自己一份常量
* 2, 依然导出，但是不能在dynamic初始化中有依赖顺序（要么compilation-initialization编译器初始化（因为就在一个编译单元里面））
* https://pabloariasal.github.io/2020/01/02/static-variable-initialization/
const KMatrix3f KMatrix3f::identity { KVec3f::forward, KVec3f::right, KVec3f::up };
const KMatrix3f KMatrix3f::zero {};

const KMatrix3i KMatrix3i::identity { KVec3i::forward, KVec3i::right, KVec3i::up };
const KMatrix3i KMatrix3i::zero {};

const KMatrix2f KMatrix2f::identity { KVec2f::right, KVec2f::up };
const KMatrix2f KMatrix2f::zero {};

const KMatrix2i KMatrix2i::identity { KVec2i::right, KVec2i::up };
const KMatrix2i KMatrix2i::zero {};
*/

const KMatrix3f KMatrix3f::identity { KVec3f {1.f, 0.f, 0.f}, KVec3f {0.f, 1.f, 0.f}, KVec3f {0.f, 0.f, 1.f} };
const KMatrix3f KMatrix3f::zero {};

const KMatrix3i KMatrix3i::identity { KVec3i {1, 0, 0}, KVec3i { 0, 1, 0}, KVec3i {0, 0, 1} };
const KMatrix3i KMatrix3i::zero {};

const KMatrix2f KMatrix2f::identity { KVec2f {1.f, 0.f}, KVec2f {0.f, 1.f} };
const KMatrix2f KMatrix2f::zero {};

const KMatrix2i KMatrix2i::identity { KVec2i {1, 0}, KVec2i {0, 1} };
const KMatrix2i KMatrix2i::zero {};

}