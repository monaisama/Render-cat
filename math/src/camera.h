#pragma once

#include "vec.h"
#include "matrix.h"

namespace KMath
{

class KCamera
{
public:
    KCamera() = delete;
    KCamera(const KCamera&) = default;
    KCamera(KCamera&&) = default;
    KCamera& operator=(const KCamera&) = default;
    KCamera& operator=(KCamera&&) = default;

    // 正交投影相机
    static KCamera Ortho(KVec3f location, KRotatorf rotaion,  float near, float far, float width, float height);
    // 透视投影相机
    static KCamera Persp();

protected:
    KCamera(const KMatrix4f& camMatrix) : viewMatrix(camMatrix.Inverse()) { }

protected:
    KMatrix4f viewMatrix;
};

}