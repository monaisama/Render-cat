#pragma once

#include "compile_header.h"
#include "vec.h"
#include "matrix.h"
#include "transform/rotator.h"

namespace KMath
{

class K_API KCamera
{
public:
    KCamera(const KCamera&) = default;
    KCamera(KCamera&&) = default;
    KCamera& operator=(const KCamera&) = default;
    KCamera& operator=(KCamera&&) = default;

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

}