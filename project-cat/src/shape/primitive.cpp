#include "primitive.h"

namespace KCore::Shape
{

KPrimitive::KPrimitive()
{
}

void KPrimitive::Setup()
{
    SetupShape();

    InnerLoadShader();
    InnerGenGLObject();
}

void KPrimitive::InnerGenGLObject()
{
    std::vector<float> data;
    data.reserve(GetMeta()->vertexs.size() + GetMeta()->colors.size());
    for (size_t i = 0; i < GetMeta()->vertexs.size(); i += 3) // 这里保证数据一定是正确的
    {
        data.push_back(GetMeta()->vertexs.at(i));
        data.push_back(GetMeta()->vertexs.at(i+1));
        data.push_back(GetMeta()->vertexs.at(i+2));

        if (i < GetMeta()->colors.size())
        {
            data.push_back(GetMeta()->colors.at(i));
            data.push_back(GetMeta()->colors.at(i+1));
            data.push_back(GetMeta()->colors.at(i+2));
        }
    }

    RenderInfo.bUseEBO = GetMeta()->indices.size() > 0;
    bool bHasColor = GetMeta()->colors.size() > 0;
    glGenBuffers(1, &RenderInfo.vbo);
    if (RenderInfo.bUseEBO)
        glGenBuffers(1, &RenderInfo.ebo);
    glCreateVertexArrays(1, &RenderInfo.vao);
    glBindVertexArray(RenderInfo.vao);
    {
        RenderInfo.count = data.size() / 3;
        if (RenderInfo.bUseEBO)
        {
            const std::vector<int32_t>& indices = GetMeta()->indices;
            RenderInfo.count = indices.size();
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RenderInfo.ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int32_t), indices.data(), GL_STATIC_DRAW);
        }
        glBindBuffer(GL_ARRAY_BUFFER, RenderInfo.vbo);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
        uint32_t stride = 3 + (bHasColor ? 3 : 0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * stride, (void*)0);
        glEnableVertexAttribArray(0);
        if (bHasColor)
        {
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * stride, (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);
        }
    }
    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    if (bHasColor) glDisableVertexAttribArray(1);
    glBindBuffer(GL_VERTEX_ARRAY, 0);
    if (RenderInfo.bUseEBO) glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void KPrimitive::InnerLoadShader()
{
    mat = new KCore::Shader::KMat(GetMeta()->Mat);
}

void KPrimitive::Render()
{
    RenderPhase(ERenderPhase::Begin);
    if (mat) // 这里是否一定不再判定default mat
        mat->Use();
    RenderPhase(ERenderPhase::AfterSetMat);
    glBindVertexArray(RenderInfo.vao);
    {
        RenderPhase(ERenderPhase::AfterBinding);
        if (RenderInfo.bUseEBO)
            glDrawElements(GL_TRIANGLES, RenderInfo.count, GL_UNSIGNED_INT, 0);
        else
            glDrawArrays(GL_TRIANGLES, 0, RenderInfo.count);
    }
    glBindVertexArray(0);
    RenderPhase(ERenderPhase::Finish);
}

KPrimitive::~KPrimitive()
{
    if (mat)
    {
        // collect mat
        delete mat; // todo: should modify using shaderlib to collect
    }
    glDeleteVertexArrays(1, &RenderInfo.vao);
    glDeleteBuffers(1, &RenderInfo.vbo);
    if (RenderInfo.bUseEBO)
        glDeleteBuffers(1, &RenderInfo.ebo);
}

}