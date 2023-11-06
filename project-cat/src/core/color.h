#pragma once

#include "vecs/vec4.h"
#include "GL/glew.h"
#include <cstdint>

namespace KCore
{

enum class EColorType : uint32_t
{
    rgb = GL_RGB,
    rgba = GL_RGBA,
};

class KColor : public KMath::KVec4<float>
{
public:
    static const KColor green;
    static const KColor blue;
    static const KColor red;
    static const KColor white;
    static const KColor black;

public:
    KColor() = default;
    KColor(float r, float g, float b, float a = 1.f): KMath::KVec4<float>(r, g, b, a) { }

    const float& R() const { return X(); }
    const float& G() const { return Y(); }
    const float& B() const { return Z(); }
    const float& A() const { return W(); }
    
    float& R() { return X(); }
    float& G() { return Y(); }
    float& B() { return Z(); }
    float& A() { return W(); }

    const float* RGBA() const { return XYZW(); }
};

}