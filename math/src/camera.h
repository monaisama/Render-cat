#pragma once

#include "compile_header.h"
#include "patterns.h"
#include "vec.h"
#include "matrix.h"
#include "transform/rotator.h"

namespace KMath
{

class KCameraTransformer;

class K_API KCamera
{
    friend class KCameraTransformer;
    GEN_DEFAULT_CONTRUCTOR_CODE(KCamera)

public:
    // 正交投影相机
    static KCamera Ortho(float near, float far, float width, float height);
    // 透视投影相机
    static KCamera Persp(float fov, float near, float far, float aspect);

    KCamera& LookAt(const KVec3f& location, const KVec3f& target);

    KMatrix4f Matrix() const { return viewMatrix * clipMatrix; }
    const KMatrix4f& ViewMatrix() const { return viewMatrix; }
    const KMatrix4f& ProjectiveMatrix() const { return clipMatrix; }

protected:
    KCamera() = default;

protected:
    KMatrix4f viewMatrix;
    KMatrix4f clipMatrix;
};

class K_API KCameraTransformer final
{
    GEN_DELETE_CONTRUCTOR_CODE_DELETE(KCameraTransformer)
public:
    KCameraTransformer(KCamera&);

    KVec3f GetRight();
    KVec3f GetForward();
    void MoveForward(KVec3f vec);
    void MoveRight(KVec3f vec);
    void RotateYaw(float angle);
    void RotatePitch(float angle);
    void MoveThenLookAt(KVec3f vec, KVec3f point);

private:
    KCamera& camera;
};

}