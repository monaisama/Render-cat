#pragma once

#include "core/asset.h"
#include "core/color.h"

namespace KCore
{

enum class ETextureType : uint32_t
{
    Texture1d = GL_TEXTURE_1D, // not support
    Texture2d = GL_TEXTURE_2D,
    Texture3d = GL_TEXTURE_3D // not support 
};

enum class ETextureSampleType : uint32_t
{
    Linear = GL_LINEAR,
    Nearest = GL_NEAREST,
    MipmapLinearLinear = GL_LINEAR_MIPMAP_LINEAR,
    MipmapLinearNearest = GL_LINEAR_MIPMAP_NEAREST,
    MipmapNearestLinear = GL_NEAREST_MIPMAP_LINEAR,
    MipmapNearestNearest = GL_NEAREST_MIPMAP_NEAREST
};

enum class ETextureWrapMode : uint32_t
{
    Repeat = GL_REPEAT,
    MirroredRepeat = GL_MIRRORED_REPEAT,
    ClampToEdge = GL_CLAMP_TO_EDGE,
    ClampToBorder = GL_CLAMP_TO_BORDER
};

struct KTextureMeta : IMeta
{
    std::string filePath;

    ETextureType type;
    bool bAutoMipmap;
    ETextureSampleType sampleTypeMin, sampleTypeMag;
    ETextureWrapMode wrapMode;
    EColorType storageColorType;

    int32_t mipmapLevel; // always 0

    std::optional<KColor> borderColor;
};

class KTexture : public KAsset
{
public:
    struct TextureRawData
    {
        uint8_t* data;
        int32_t width, height;
        uint8_t channels;
    };

    KTexture(const KTextureMeta&, const TextureRawData& data);
    virtual const KTextureMeta* GetMeta() const override { return &metaInfo; }

    virtual ~KTexture();

protected:
    KTextureMeta metaInfo;

    GLuint textureID;
};

}