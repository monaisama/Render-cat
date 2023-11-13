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

    const float& R() const { return x; }
    const float& G() const { return y; }
    const float& B() const { return z; }
    const float& A() const { return w; }
    
    float& R() { return x; }
    float& G() { return y; }
    float& B() { return z; }
    float& A() { return w; }

    const float* RGBA() const { return xyzw; }
};

}