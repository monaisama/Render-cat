#pragma once
#include "core/core.h"
#include "core/asset.h"

#include "mat/mat.h"
#include "mat/texture.h"

#include "core/render.h"

namespace KCore
{

// todo.. �����metaҲû��̫��� Ϲд��
struct KShapeMeta : IMeta
{
    // Ҳ�����Ӧ������Դ����ɶ��
    std::vector<float> vertexs;
    std::vector<float> colors;
    std::vector<float> corrds;
    std::vector<int32_t> indices;

    KMatMeta mat;
    std::vector<KTextureMeta> texs;
};

/* 
* ���嶥�㣬��ɫ��matrial��render �ȵ�
*/
class KPrimitive : public KAsset
{
public:
    KPrimitive();
    void Setup();
    virtual void Render(const KRender&);

    virtual ~KPrimitive();

    virtual const KShapeMeta* GetMeta() const override { return &metaInfo; }
    
protected:
    enum class ERenderPhase : uint8_t
    {
        Begin,
        AfterSetMat,
        AfterBinding,
        Finish,
    };
    virtual void SetupShape() { } // none
    virtual void RenderPhase(ERenderPhase phase, const KRender&) { }

protected:
    std::shared_ptr<KMat> mat;
    std::vector<std::shared_ptr<KTexture>> texs;

    KShapeMeta metaInfo;

private:
    struct
    {
        GLuint vbo;
        GLuint vao;
        GLuint ebo;

        bool bUseEBO;
        uint32_t count;
    } renderInfo;

    void InnerLoadShader();
    void InnerGenGLObject();
};

}