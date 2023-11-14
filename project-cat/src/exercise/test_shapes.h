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

class KExerciseShape : public KPrimitive
{
protected:
    virtual void SetupShape() override
    {
        metaInfo.vertexs = {
            -0.5f, -0.5f, 0.f,
            0.f, 0.5f, 0.f,
            0.5f, -0.5f, 0.f
        };

        metaInfo.colors = {
            1.f, 0.f, 0.f,
            0.f, 1.f, 0.f,
            0.f, 0.f, 1.f
        };

        metaInfo.indices = {
            0,1,2
        };

        metaInfo.mat = KUtils::MakeMetaMat(
            KUtils::MakeMetaShader("exercise.vs", KShaderType::Vertex),
            KUtils::MakeMetaShader("exercise.fs", KShaderType::Fragment)
        );
    }

    virtual void RenderPhase(ERenderPhase phase)
    {
        using namespace KMath;
        auto translateMat = MakeTranslateMatrix<float, float>(KVec3f { 0.3f, 0.3f, 0 });
        auto rotationMat = MakeRotateMatrix<float, float>(KVec3f::up, glfwGetTime());
        switch (phase)
        {
            case ERenderPhase::AfterSetMat:
                // mat->SetMatrix4f("matrix", translateMat * KMatrix4f { rotationMat });
                mat->SetMatrix4f("matrix", KMatrix4f { rotationMat } * translateMat);
                break;
            default:
                break;
        }
    }
};