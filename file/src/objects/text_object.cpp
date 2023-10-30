#include "text_object.h"

std::fstream& operator<<(std::fstream& out, const KTextObject& object)
{
    for (const auto& vertex : object.vertexs)
        out << vertex << "\n";
    // out << "\n";
    // out << object.vertexShader << '\n' << object.fragmentShader;
    return out;
}

std::fstream& operator<<(std::fstream& out, const KTextVertex& vertex)
{
    out << vertex.vertex << "\n";
    out << vertex.color << "\n";
    return out;
}

std::fstream& operator<<(std::fstream& out, const KVec3f& vec3f)
{
    out << vec3f.x << " " << vec3f.y << " " << vec3f.z;
    return out;
}

std::fstream& operator>>(std::fstream& in, KVec3f& vec3f)
{
    in >> vec3f.x >> vec3f.y >> vec3f.z;
    return in;
}

std::fstream& operator>>(std::fstream& in, KTextVertex& vertex)
{
    in >> vertex.vertex >> vertex.color;
    return in;
}

std::fstream& operator>>(std::fstream& in, KTextObject& object)
{
    std::vector<KTextVertex> vertexs;
    KTextVertex tempVertex;
    while (in >> tempVertex)
    {
        vertexs.push_back(tempVertex);
    }
    return in;
}