#include "matrix.h"
#include "vec.h"

namespace KMath
{

/* ill-format ���� dynamic-initialization˳��ȷ�������Կ���forward���ܻ�û�г�ʼ�����
* 1, �� right forward ��Щд�ڶ�Ӧvec��template ��.h �ļ��� �������������Ļ��Ϳ���ÿһ�����뵥Ԫ�Լ�һ�ݳ���
* 2, ��Ȼ���������ǲ�����dynamic��ʼ����������˳��Ҫôcompilation-initialization��������ʼ������Ϊ����һ�����뵥Ԫ���棩��
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

// --- 3x3
const KMatrix3f KMatrix3f::identity { KVec3f {1.f, 0.f, 0.f}, KVec3f {0.f, 1.f, 0.f}, KVec3f {0.f, 0.f, 1.f} };
const KMatrix3f KMatrix3f::zero {};

const KMatrix3i KMatrix3i::identity { KVec3i {1, 0, 0}, KVec3i { 0, 1, 0}, KVec3i {0, 0, 1} };
const KMatrix3i KMatrix3i::zero {};

// --- 2x2
const KMatrix2f KMatrix2f::identity { KVec2f {1.f, 0.f}, KVec2f {0.f, 1.f} };
const KMatrix2f KMatrix2f::zero {};

const KMatrix2i KMatrix2i::identity { KVec2i {1, 0}, KVec2i {0, 1} };
const KMatrix2i KMatrix2i::zero {};

// --- 4x4
const KMatrix4f KMatrix4f::identity { KVec4f {1, 0, 0, 0}, KVec4f {0, 1, 0, 0}, KVec4f {0, 0, 1, 0 }, KVec4f {0, 0, 0, 1} };
const KMatrix4f KMatrix4f::zero { };

const KMatrix4i KMatrix4i::identity { KVec4i {1, 0, 0, 0}, KVec4i {0, 1, 0, 0}, KVec4i {0, 0, 1, 0}, KVec4i {0, 0, 0, 1} };
const KMatrix4i KMatrix4i::zero { };

}