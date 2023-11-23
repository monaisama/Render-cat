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
    KCamera() = delete;
    KCamera(const KCamera&) = default;
    KCamera(KCamera&&) = default;
    KCamera& operator=(const KCamera&) = default;
    KCamera& operator=(KCamera&&) = default;

    // 正交投影相机
    static KCamera Ortho(const KVec3f& location, const KRotatorf& rotaion, float near, float far, float width, float height);
    // 透视投影相机
    static KCamera Persp(const KVec3f& location, const KRotatorf& rotation, float fov, float near, float far, float ratio);

    KMatrix4f Matrix() const { return viewMatrix * clipMatrix; }
    const KMatrix4f& ViewMatrix() const { return viewMatrix; }
    const KMatrix4f& ProjectiveMatrix() const { return clipMatrix; }

protected:
    KCamera(const KMatrix4f& camMatrix) : viewMatrix(camMatrix.Inverse()) { }

protected:
    KMatrix4f viewMatrix;
    KMatrix4f clipMatrix;
};

}