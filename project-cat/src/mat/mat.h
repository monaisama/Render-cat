#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>

#include "shader.h"

struct KShaderPair
{
    KShader vertexShader;
    KShader fragmentShader;
};

class KMat
{
public:
    KMat(const KShaderPair& Pair);
    ~KMat();

    void Use() const;

protected:
    GLuint matObjectID;

    GLchar logInfo[512];
};