#pragma once
#include "core/core.h"
#include "shape/primitive.h"
#include "GLFW/glfw3.h"
#include <cmath>
#include "utils/utils.h"

using namespace KCore;

class KExample : public KPrimitive
{
protected:
    virtual void SetupShape() override
    {
        MetaInfo.vertexs = {
            0.f, 0.6f, 0.f,
            0.6f, -0.6f, 0.f,
            -0.6f, -0.6f, 0.f
        };

        MetaInfo.Mat = KUtils::MakeMetaMat(
            KUtils::MakeMetaShader("default.vs", KShaderType::Vertex),
            KUtils::MakeMetaShader("default_color.fs", KShaderType::Fragment)
        );
    }
};

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

        MetaInfo.Mat = KUtils::MakeMetaMat(
            KUtils::MakeMetaShader("triangle.vs", KShaderType::Vertex),
            KUtils::MakeMetaShader("triangle.fs", KShaderType::Fragment)
        );
    }

    virtual void RenderPhase(ERenderPhase phase) override
    {
        switch (phase)
        {
            case ERenderPhase::AfterSetMat:
                mat->SetBool("offset", 0.f);
                break;
            default:
                break;
        }
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

        MetaInfo.Mat = KUtils::MakeMetaMat(
            KUtils::MakeMetaShader("triangle.vs", KShaderType::Vertex),
            KUtils::MakeMetaShader("triangle.fs", KShaderType::Fragment)
        );
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