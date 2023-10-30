#include "vecs/vec3.h"
#include "file.h"
#include "log.h"

#include "objects/text_object.h"

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

    std::string content = KFile::ReadFile("default.vs");

    KLog::Log(content);
    KLog::Log(KFileTest{}.Int());


    KTextObject object;
    for (int32_t i = 0; i < 10; i++)
    {
        object.vertexs.push_back(KTextVertex{KVec3f(i, i+1, i+2), KVec3f(i, i-1, i-2)});
    }
    KFile testStream;
    testStream.Open("testObj.txt");
    testStream.GetStream() << object;
    testStream.Close();

    KTextObject object1;
    KFile testStream1;
    testStream1.Open("testObj.txt");
    testStream1.GetStream() >> object1;
    testStream1.Close();

    KLog::Log(object.vertexs.size());
    KLog::Log(object1.vertexs.size());

#pragma endregion

    return 0;
}