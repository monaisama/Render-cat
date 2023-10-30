#pragma once
#include "core/core.h"
#include "shape/primitive.h"
#include "GLFW/glfw3.h"
#include <cmath>

using namespace KCore;
using namespace KCore::Shape;

class K_2Triangles : public KPrimitive
{
protected:
    virtual void SetupShape() override
    {
        MetaInfo.vertexs = {
            -0.5f, -0.5f, 0.f,
            0.5f, -0.5f, 0.f,
            0.5f, 0.5f, 0.f,
            -0.5, 0.5f, 0.f
        };

        MetaInfo.colors = {
            1.f, 0.f, 0.f,
            0.f, 1.f, 0.f,
            0.f, 0.f, 1.f,
            1.f, 1.f, 1.f
        };

        MetaInfo.indices = {
            0,1,2,
            0,2,3
        };

        MetaInfo.Mat.vertexFile = "triangle.vs";
        MetaInfo.Mat.fragmentFile = "triangle.fs";
    }
};

class KExcriseShape : public KPrimitive
{
protected:
    virtual void SetupShape() override
    {
        MetaInfo.vertexs = {
            -0.5f, -0.5f, 0.f,
            0.5f, -0.5f, 0.f,
            0.5f, 0.5f, 0.f,
            -0.5, 0.5f, 0.f
        };

        MetaInfo.colors = {
            1.f, 0.f, 0.f,
            0.f, 1.f, 0.f,
            0.f, 0.f, 1.f,
            1.f, 1.f, 1.f
        };

        MetaInfo.indices = {
            0,1,2,
            0,2,3
        };

        MetaInfo.Mat.vertexFile = "triangle.vs";
        MetaInfo.Mat.fragmentFile = "triangle.fs";
    }

    virtual void RenderPhase(ERenderPhase phase)
    {
        switch (phase)
        {
            case ERenderPhase::AfterSetMat:
                mat->SetFloat("offset", sin(glfwGetTime()));
                break;
            default:
                break;
        }
    }
};