#include "vecs/vec3.h"
#include "file.h"
#include "log.h"

#include <iostream>
#include <string>

using namespace KMath;
using namespace KFileUtils;

int main()
{
#pragma region test for Vec

    KVec3f vec1, vec2(1.f, 2.f, 3.f);

    vec1 += vec2;
    std::cout << vec1.x << " " << vec1.y << " " << vec1.z << std::endl;

#pragma endregion

#pragma region test file

    // KFile file;
    // file.Open("default.vs");
    // std::string content;
    // file.GetStream() >> content;
    // file.Close();

    // KLog::Log(content);
    KLog::Log(KFileTest{}.Int());

#pragma endregion

    return 0;
}