#include "camera.h"

namespace KMath
{

// 将我们自己定义的坐标系，转换到opengl的NDC定义的坐标系下
// y -> right 到 y -> up
// x -> forward 到 x -> right
// z -> up 到 z -> forward
// 仍然是左手坐标系下
KMatrix4f GetCorrdConverter2OpenglNDC()
{
    return KMatrix4f {
        KVec4f { 0.f, 0.f, 1.f, 0.f },
        KVec4f { 1.f, 0.f, 0.f, 0.f },
        KVec4f { 0.f, 1.f, 0.f, 0.f },
        KVec4f::wzero
    };
}

// 转换到裁剪空间矩阵 ndc的正方体
// 这里采用直接转换到opengl的坐标系中
// opengl的NDC使用xyz -> [-1, 1] 并且z轴向屏幕内，y轴向上，x轴向右
// 所以这里需要先映射到 [-1, 1]的正方体中
KMatrix4f MakeClipSpaceNDC(float near, float far, float width, float height) // ortho
{
    // 下面所有的计算都是在NDC坐标系空间中
    const float midz = (far - near) / 2;
    KMatrix4f trans = MakeTranslateMatrix(KVec3f {0, 0, midz}).Inverse(); // 位移到原点
    KMatrix4f scale = ToMatrix4(MakeScaleMatrix(KVec3f(width / 2, height / 2, midz)).Inverse()); // 缩放到正方体中

    // KLog::LogSimple("trans & scale:\n", trans, scale);
    return GetCorrdConverter2OpenglNDC() * // 转换坐标系
        trans * scale;
}

KCamera KCamera::Ortho(const KVec3f& location, const KRotatorf& rotation, float near, float far, float width, float height)
{
    KCamera camera(MakeTranslateMatrix(location)); // todo rotation
    camera.clipMatrix = MakeClipSpaceNDC(near, far, width, height);
    return camera;
}

}