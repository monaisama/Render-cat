#include "camera.h"
#include <cmath>
#include "mymath.h"

namespace KMath
{

// �������Լ����������ϵ��ת����opengl��NDC���������ϵ��
// y -> right �� y -> up
// x -> forward �� x -> right
// z -> up �� z -> forward
// ��Ȼ����������ϵ��
KMatrix4f GetCorrdConverter2OpenglNDC()
{
    return KMatrix4f {
        KVec4f { 0.f, 0.f, 1.f, 0.f },
        KVec4f { 1.f, 0.f, 0.f, 0.f },
        KVec4f { 0.f, 1.f, 0.f, 0.f },
        KVec4f::wzero
    };
}

// ת�����ü��ռ���� ndc��������
// �������ֱ��ת����opengl������ϵ��
// opengl��NDCʹ��xyz -> [-1, 1] ����z������Ļ�ڣ�y�����ϣ�x������
// ����������Ҫ��ӳ�䵽 [-1, 1]����������
// ����ͶӰ
KMatrix4f MakeClipSpaceNDC_Ortho(float near, float far, float width, float height) // ortho
{
    const float midz = (far - near) / 2;
    KMatrix4f trans = MakeTranslateMatrix(KVec3f {midz, 0, 0}).Inverse(); // λ�Ƶ�ԭ��
    KMatrix4f scale = ToMatrix4(MakeScaleMatrix(KVec3f(midz, width / 2, height / 2)).Inverse()); // ���ŵ���������

    // KLog::LogSimple("trans & scale:\n", trans, scale);
    return trans * scale * GetCorrdConverter2OpenglNDC(); // ת������ϵ
}

// ͸��ͶӰ
// ����ٶ�ͶӰƽ���Ǿ���ԭ��λ��d = 1(������벻��Ҫ����ͬ�����Ӧ��С����Ļ��ռ����һ�µ�)
KMatrix4f MakeClipSpaceNDC_Persp(float fov, float near, float far, float aspect)
{
    // ���ŵ��������� // ������ʵ���ǽ���׶��ѹ������������
    // ���ü��� n Զ�ü��� f, ����(n,0,0,1) ӳ��� n���䣬��f,0,0,1�� ӳ���f����
    // ���������������������Ӧ�ľ��� y` = y * n/x��Ȼ��ֱ�����������(x`,y,z,x)
    KMatrix4f zoom {
        KVec4f {near + far, 0, 0, 1},
        KVec4f {0, near, 0, 0},
        KVec4f {0, 0, near, 0},
        KVec4f {-near * far, 0, 0, 0},
    };
    // ѹ����һ��������֮����Ҫִ������ͶӰ�任
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