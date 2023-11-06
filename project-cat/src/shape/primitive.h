#pragma once
#include "core/core.h"
#include "core/asset.h"

#include "mat/mat.h"

namespace KCore
{

// todo.. 这里的meta也没搞太清楚 瞎写的
struct KShapeMeta : IMeta
{
    // 也许后面应该是资源个是啥的
    std::vector<float> vertexs;
    std::vector<float> colors;
    std::vector<int32_t> indices;

    KMatMeta Mat;
};

/* 
* 定义顶点，颜色，matrial，render 等等
*/
class KPrimitive : public KAsset
{
public:
    KPrimitive();
    void Setup();
    virtual void Render();

    virtual ~KPrimitive();

    virtual const KShapeMeta* GetMeta() const override { return &MetaInfo; }
    
protected:
    enum class ERenderPhase : uint8_t
    {
        Begin,
        AfterSetMat,
        AfterBinding,
        Finish,
    };
    virtual void SetupShape() { } // none
    virtual void RenderPhase(ERenderPhase phase) { }

protected:
    std::shared_ptr<KMat> mat;

    KShapeMeta MetaInfo;

private:
    struct
    {
        GLuint vbo;
        GLuint vao;
        GLuint ebo;

        bool bUseEBO;
        uint32_t count;
    } RenderInfo;

    void InnerLoadShader();
    void InnerGenGLObject();
};

}