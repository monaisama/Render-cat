#include "camera.h"
#include <cmath>
#include "mymath.h"

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
// 正交投影
KMatrix4f MakeClipSpaceNDC_Ortho(float near, float far, float width, float height) // ortho
{
    const float midz = (far - near) / 2;
    KMatrix4f trans = MakeTranslateMatrix(KVec3f {midz, 0, 0}).Inverse(); // 位移到原点
    KMatrix4f scale = ToMatrix4(MakeScaleMatrix(KVec3f(midz, width / 2, height / 2)).Inverse()); // 缩放到正方体中

    // KLog::LogSimple("trans & scale:\n", trans, scale);
    return trans * scale * GetCorrdConverter2OpenglNDC(); // 转换坐标系
}

// 透视投影
// 这里假定投影平面是距离原点位置d = 1(这个距离不重要，不同距离对应大小在屏幕的占比是一致的)
KMatrix4f MakeClipSpaceNDC_Persp(float fov, float near, float far, float aspect)
{
    // 缩放到正方体中 // 这里其实就是将视锥体压缩到立方体中
    // 近裁剪面 n 远裁剪面 f, 根据(n,0,0,1) 映射后 n不变，（f,0,0,1） 映射后f不变
    // 根据相似三角形来计算对应的矩阵 y` = y * n/x，然后直接其次坐标变成(x`,y,z,x)
    KMatrix4f zoom {
        KVec4f {near + far, 0, 0, 1},
        KVec4f {0, near, 0, 0},
        KVec4f {0, 0, near, 0},
        KVec4f {-near * far, 0, 0, 0},
    };
    // 压缩成一个立方体之后，需要执行正交投影变换
    float radian = Radians(fov / 2.f);
    float height = 2 * near / tan(radian);
    return zoom * MakeClipSpaceNDC_Ortho(near, far, height * aspect, height);
}

KCamera KCamera::Ortho(float near, float far, float width, float height)
{
    KCamera camera {};
    camera.clipMatrix = MakeClipSpaceNDC_Ortho(near, far, width, height);
    return camera;
}

KCamera KCamera::Persp(float fov, float near, float far, float aspect)
{
    KCamera camera {};
    camera.clipMatrix = MakeClipSpaceNDC_Persp(fov, near, far, aspect);
    return camera;
}

KCamera& KCamera::LookAt(const KVec3f& location, const KVec3f& target)
{
    viewMatrix = KMath::LookAt(location, target).Inverse();
    return *this;
}

KCamera& KCamera::LookAt(const KVec3f& target)
{
    viewMatrix = KMath::LookAt(viewMatrix.Inverse() * KVec3f::zero, target).Inverse();
    return *this;
}

KCameraTransformer::KCameraTransformer(KCamera& camera)
    : camera(camera) { }

KVec3f KCameraTransformer::GetRight()
{
    return camera.viewMatrix.Inverse() * KVec3f::right;
}

KVec3f KCameraTransformer::GetForward()
{
    return camera.viewMatrix.Inverse() * KVec3f::forward;
}

KVec3f KCameraTransformer::GetUp()
{
    return camera.viewMatrix.Inverse() * KVec3f::up;
}

void KCameraTransformer::MoveForward(float dis)
{
    MoveLocal(KVec3f::forward * dis);
}

void KCameraTransformer::MoveRight(float dis)
{
    MoveLocal(KVec3f::right * dis);
}

void KCameraTransformer::MoveUp(float dis)
{
    MoveLocal(KVec3f::up * dis);
}

void KCameraTransformer::MoveLocal(const KVec3f& vec)
{
    camera.viewMatrix = (camera.viewMatrix.Inverse() * MakeTranslateMatrix(vec)).Inverse();
}

void KCameraTransformer::RotateYaw(float angle)
{
    RotateLocal(KVec3f::up, angle);
}

void KCameraTransformer::RotatePitch(float angle)
{
    RotateLocal(KVec3f::right, angle);
}

void KCameraTransformer::RotateRoll(float angle)
{
    RotateLocal(KVec3f::forward, angle);
}

void KCameraTransformer::RotateLocal(const KVec3f& axis, float angle)
{
    camera.viewMatrix = (camera.viewMatrix.Inverse() * ToMatrix4(MakeRotateMatrix(axis, angle))).Inverse();
}

void KCameraTransformer::MoveThenLookAt(const KVec3f& vec, const KVec3f& point)
{
    MoveLocal(vec);
    camera.LookAt(point);
}

}