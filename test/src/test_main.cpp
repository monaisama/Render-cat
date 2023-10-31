#include <functional>
#include "vecs/vec3.h"
#include "file.h"
#include "log.h"

#include "objects/text_object.h"

#include <iostream>
#include <string>
#include <array>
#include <any>

using namespace KMath;
using namespace KFileUtils;

template<class... Args>
void ArgsFunc(Args... args)
{
    std::array<std::function<void()>, sizeof...(Args)> params {
        ([&args]()
        {
            std::cout << std::boolalpha << args << " || " << std::noboolalpha;
        })...
    };

    for (auto& f : params)
    {
        std::invoke(f);
    }

    std::any a = 10000;
    int32_t ia = std::any_cast<int32_t>(a);
    std::cout << ia << std::endl;
}

int main()
{
    KLog::Log("failed");
    KLog::LogError("error");
    KLog::LogError("start {0} - {1} middle\{} {0} {2} bool {3} logend", -1, 100.1f, "hello log", true);

    return 0;

    int32_t a = 10;
    std::reference_wrapper<int32_t>  ra = a;
    ra.get() = 100;
    auto rra = std::ref(a);
    rra.get() = 1;

    KLog::Log(a);

    // std::initializer_list<int32_t> iarr {1, 2, 3};
    // for (auto i : iarr)
    // {
    //     KLog::Log(i);
    // }

    // std::array<int32_t, 10> arr {};
    // for (auto ele : arr)
    // {
    //     KLog::Log(ele);
    // }

    ArgsFunc(1, 2, 3, 10.111f);

    KLog::Log("{0} {1}", 100, -1);

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