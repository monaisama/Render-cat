#include "primitive.h"
#include "resource/resources.h"

namespace KCore
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
    // 这里可以生成很多个abo对象，然后binding多个数据吧 todo.. 待测试，不知道这样abo中会不会存储了unbind的信息
    std::vector<float> data;
    data.reserve(GetMeta()->vertexs.size() + GetMeta()->colors.size() + GetMeta()->corrds.size());
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

        std::size_t j = i / 3 * 2;
        if (j < GetMeta()->corrds.size())
        {
            data.push_back(GetMeta()->corrds.at(j));
            data.push_back(GetMeta()->corrds.at(j+1));
        }
    }

    renderInfo.bUseEBO = GetMeta()->indices.size() > 0;
    bool bHasColor = GetMeta()->colors.size() > 0;
    bool bHasTex = GetMeta()->corrds.size() > 0;
    glGenBuffers(1, &renderInfo.vbo);
    if (renderInfo.bUseEBO)
        glGenBuffers(1, &renderInfo.ebo);
    glCreateVertexArrays(1, &renderInfo.vao);
    glBindVertexArray(renderInfo.vao);
    {
        renderInfo.count = data.size() / 3;
        if (renderInfo.bUseEBO)
        {
            const std::vector<int32_t>& indices = GetMeta()->indices;
            renderInfo.count = indices.size();
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderInfo.ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int32_t), indices.data(), GL_STATIC_DRAW);
        }
        glBindBuffer(GL_ARRAY_BUFFER, renderInfo.vbo);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
        uint32_t stride = 3 + (bHasColor ? 3 : 0) + (bHasTex ? 2 : 0);
        uint32_t location = 0, offset = 0;
        glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, sizeof(float) * stride, (void*)offset);
        glEnableVertexAttribArray(location);
        offset += 3;
        location++;
        if (bHasColor)
        {
            glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, sizeof(float) * stride, (void*)(offset * sizeof(float)));
            glEnableVertexAttribArray(location);
            offset += 3;
            location++;
        }
        if (bHasTex)
        {
            glVertexAttribPointer(location, 2, GL_FLOAT, GL_FALSE, sizeof(float) * stride, (void*)(offset * sizeof(float)));
            glEnableVertexAttribArray(location);
            location++;
            offset += 2;
        }
    }
    glBindVertexArray(0);
    uint32_t location = 0;
    glDisableVertexAttribArray(location++);
    if (bHasColor) glDisableVertexAttribArray(location++);
    if (bHasTex) glDisableVertexAttribArray(location++);
    glBindBuffer(GL_VERTEX_ARRAY, 0);
    if (renderInfo.bUseEBO) glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void KPrimitive::InnerLoadShader()
{
    mat = KResources::GetInstance().Load<KMat, KMatMeta>(GetMeta()->mat);
    if (GetMeta()->corrds.size() > 0) // has texture
    {
        texs.reserve(GetMeta()->texs.size());
        for (size_t i = 0; i < GetMeta()->texs.size(); ++i)
            texs.push_back(KResources::GetInstance().Load<KTexture, KTextureMeta>(GetMeta()->texs[i]));
    }
}

void KPrimitive::Render()
{
    RenderPhase(ERenderPhase::Begin);
    if (mat) // 这里是否一定不再判定default mat
    {
        mat->Use();
        for (size_t i = 0; i < texs.size(); ++i)
        {
            mat->SetInt(std::string{"tex"}.append(std::to_string(i)), i);
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(texs[i]->GetTextureType(), texs[i]->GetTexture());
        }
    }
    RenderPhase(ERenderPhase::AfterSetMat);
    glBindVertexArray(renderInfo.vao);
    {
        RenderPhase(ERenderPhase::AfterBinding);
        if (renderInfo.bUseEBO)
            glDrawElements(GL_TRIANGLES, renderInfo.count, GL_UNSIGNED_INT, 0);
        else
            glDrawArrays(GL_TRIANGLES, 0, renderInfo.count);
    }
    glBindVertexArray(0);
    RenderPhase(ERenderPhase::Finish);
}

KPrimitive::~KPrimitive()
{
    glDeleteVertexArrays(1, &renderInfo.vao);
    glDeleteBuffers(1, &renderInfo.vbo);
    if (renderInfo.bUseEBO)
        glDeleteBuffers(1, &renderInfo.ebo);
}

}