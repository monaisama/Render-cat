#pragma once
#include "core/core.h"
#include "shape/primitive.h"
#include "GLFW/glfw3.h"
#include <cmath>
#include "utils/utils.h"

#include "camera.h"

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
            -2, -2, -2,
            -2, -2, 2,
            2, -2, 2,
            2, -2, -2,
            2, 2, -2,
            2, 2, 2,
            -2, 2, 2,
            -2, 2, -2
        };

        metaInfo.colors = {
            1.f, 0.f, 0.f,
            0.f, 1.f, 0.f,
            0.f, 0.f, 1.f,
            1.f, 0.f, 0.f,
            0.f, 1.f, 0.f,
            0.f, 0.f, 1.f,
            1.f, 0.f, 0.f,
            0.f, 1.f, 0.f
        };

        metaInfo.indices = {
            0,1,2,
            0,2,3,
            0,1,6,
            0,6,7,
            1,2,6,
            2,5,6,
            2,4,3,
            2,5,4,
            3,7,0,
            3,4,7,
            5,7,6,
            5,4,7
        };

        // metaInfo.vertexs = {
        //     -0.25, -0.333333, 0.010101,
        //     0.25, -0.333333, 0.010101,
        //     0, 0.333333, 0.010101 
        // };

        // metaInfo.vertexs = {
        //     0, -1, -1,
        //     0, 1, -1,
        //     0, 0, 1
        // };
        
        // metaInfo.colors = {
        //     1.f, 0.f, 0.f,
        //     0.f, 1.f, 0.f,
        //     0.f, 0.f, 1.f,
        // };

        // metaInfo.indices = {
        //     0,1,2
        // };

        metaInfo.mat = KUtils::MakeMetaMat(
            KUtils::MakeMetaShader("exercise.vs", KShaderType::Vertex),
            KUtils::MakeMetaShader("exercise.fs", KShaderType::Fragment)
        );
    }

    virtual void RenderPhase(ERenderPhase phase)
    {
        using namespace KMath;
        KCamera camera = KCamera::Ortho( {-5, 0, 0}, {0, 0, 0}, 0.1f, 10.f, 80, 60);
        auto translateMat = MakeTranslateMatrix<float, float>(KVec3f { 0.3f, 0.3f, 0 });
        auto rotationMat = MakeRotateMatrix<float, float>(KVec3f::up, glfwGetTime());

        // KLog::LogSimple(KVec3f{0,-1,-1} * camera.Matrix());
        // KLog::LogSimple(KVec3f{0,1,-1} * camera.Matrix());
        // KLog::LogSimple(KVec3f{0,0,1} * camera.Matrix());

        // KLog::LogSimple(camera.Matrix());
        switch (phase)
        {
            case ERenderPhase::AfterSetMat:
                mat->SetMatrix4f("matrix", camera.Matrix());
                break;
            default:
                break;
        }
    }
};