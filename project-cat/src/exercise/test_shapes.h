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
        metaInfo.vertexs = {
            -1.f, -1.f, 0.f,
            -1.f, 1.f, 0.f,
            1.f, -1.f, 0.f,
            1.f, 1.f, 0.f
        };

        metaInfo.indices = {
            0, 1, 2,
            1, 2, 3
        };

        metaInfo.corrds = {
            0.f, 0.f,
            0.f, 1.f,
            1.f, 0.f,
            1.f, 1.f,
        };

        metaInfo.mat = KUtils::MakeMetaMat(
            KUtils::MakeMetaShader("default_texture.vs", KShaderType::Vertex),
            KUtils::MakeMetaShader("default_texture.fs", KShaderType::Fragment)
        );

        metaInfo.texs = {
            KUtils::MakeMetaTexture("namei_1.png",
            ETextureSampleType::Nearest,
            ETextureWrapMode::Repeat,
            EColorType::rgb),

            KUtils::MakeMetaTexture("namei_2.png",
            ETextureSampleType::Nearest,
            ETextureWrapMode::Repeat,
            EColorType::rgb)
        };
    }
};

class K_2Triangles : public KPrimitive
{
protected:
    virtual void SetupShape() override
    {
        metaInfo.vertexs = {
            -0.5f, -0.5f, 0.f,
            0.5f, -0.5f, 0.f,
            0.5f, 0.5f, 0.f,
            -0.5, 0.5f, 0.f
        };

        metaInfo.colors = {
            1.f, 0.f, 0.f,
            0.f, 1.f, 0.f,
            0.f, 0.f, 1.f,
            1.f, 1.f, 1.f
        };

        metaInfo.indices = {
            0,1,2,
            0,2,3
        };

        metaInfo.mat = KUtils::MakeMetaMat(
            KUtils::MakeMetaShader("triangle.vs", KShaderType::Vertex),
            KUtils::MakeMetaShader("triangle.fs", KShaderType::Fragment)
        );
    }

    virtual void RenderPhase(ERenderPhase phase) override
    {
        switch (phase)
        {
            case ERenderPhase::AfterSetMat:
                mat->SetFloat("offset", 0.f);
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
        metaInfo.vertexs = {
            -0.5f, -0.5f, 0.f,
            0.5f, -0.5f, 0.f,
            0.5f, 0.5f, 0.f,
            -0.5, 0.5f, 0.f
        };

        metaInfo.colors = {
            1.f, 0.f, 0.f,
            0.f, 1.f, 0.f,
            0.f, 0.f, 1.f,
            1.f, 1.f, 1.f
        };

        metaInfo.indices = {
            0,1,2,
            0,2,3
        };

        metaInfo.mat = KUtils::MakeMetaMat(
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