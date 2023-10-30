#pragma once
// 用于处理一些预定义好的用于测试的基础图形 cube sphere 等等（这里的object类型只是测试用的）

#include "vecs/vec3.h"
#include <vector>
#include <string>
#include <fstream>

using namespace KMath;

struct K_API KTextVertex
{
    KVec3f vertex;
    KVec3f color;
};

struct K_API KTextObject
{
    std::vector<KTextVertex> vertexs;
    // std::string vertexShader;
    // std::string fragmentShader;
};

K_API std::fstream& operator<<(std::fstream&, const KVec3f&);
K_API std::fstream& operator<<(std::fstream&, const KTextVertex&);
K_API std::fstream& operator<<(std::fstream&, const KTextObject&);

K_API std::fstream& operator>>(std::fstream&, KVec3f&);
K_API std::fstream& operator>>(std::fstream&, KTextVertex&);
K_API std::fstream& operator>>(std::fstream&, KTextObject&);

