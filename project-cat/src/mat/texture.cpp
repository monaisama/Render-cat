#include "texture.h"
#include "log.h"

namespace KCore
{

KTexture::KTexture(const KTextureMeta& meta, const KTexture::TextureRawData& data)
{
    metaInfo = meta;

    if (metaInfo.type != ETextureType::Texture2d)
    {
        KLog::LogSimpleError("not support texture type", GetTextureType());
        return;
    }

    GLenum textureType = GetTextureType();

    glGenTextures(1, &textureID);
    glBindTexture(textureType, textureID);
    glTexParameteri(textureType, GL_TEXTURE_WRAP_S, static_cast<GLenum>(metaInfo.wrapMode));
    glTexParameteri(textureType, GL_TEXTURE_WRAP_T, static_cast<GLenum>(metaInfo.wrapMode));
    glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, static_cast<GLenum>(metaInfo.sampleTypeMin));
    glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, static_cast<GLenum>(metaInfo.sampleTypeMag));

    if (metaInfo.wrapMode == ETextureWrapMode::ClampToBorder)
    {
        if (!metaInfo.borderColor.has_value())
        {
            KLog::LogSimpleError("Texture meta data bordercolor error(need set value).");
            glBindTexture(textureType, 0);
            glDeleteTextures(1, &textureID);
            return;
        }
        const auto& color = metaInfo.borderColor.value();
        glTexParameterfv(textureType, GL_TEXTURE_BORDER_COLOR, color.RGBA());
    }

    EColorType sourceColorType = data.channels == 4 ? EColorType::rgba : EColorType::rgb;
    glTexImage2D(textureType, metaInfo.mipmapLevel, static_cast<GLenum>(metaInfo.storageColorType),
        data.width, data.height, 0, static_cast<GLenum>(sourceColorType), GL_UNSIGNED_BYTE, data.data);
    if (metaInfo.bAutoMipmap)
        glGenerateMipmap(textureType);
    
    glBindTexture(textureType, 0); // unbind now
}

KTexture::~KTexture()
{
    if (glIsTexture(textureID))
        glDeleteTextures(1, &textureID);
}

}