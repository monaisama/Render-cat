#include "text_object.h"

std::fstream& operator<<(std::fstream& out, const KTextObject& object)
{
    for (const auto& vertex : object.vertexs)
        out << vertex;
    // out << "\n";
    // out << object.vertexShader << '\n' << object.fragmentShader;
    return out;
}

std::fstream& operator<<(std::fstream& out, const KTextVertex& vertex)
{
    out << vertex.vertex;
    out << vertex.color;
    return out;
}

std::fstream& operator<<(std::fstream& out, const KVec3f& vec3f)
{
    out << vec3f.X() << " " << vec3f.Y() << " " << vec3f.Z() << std::endl;
    return out;
}

std::fstream& operator>>(std::fstream& in, KVec3f& vec3f)
{
    in >> vec3f.X() >> vec3f.Y() >> vec3f.Z();
    return in;
}

std::fstream& operator>>(std::fstream& in, KTextVertex& vertex)
{
    in >> vertex.vertex >> vertex.color;
    return in;
}

std::fstream& operator>>(std::fstream& in, KTextObject& object)
{
    KTextVertex tempVertex;
    while (in >> tempVertex)
    {
        object.vertexs.push_back(tempVertex);
    }
    return in;
}