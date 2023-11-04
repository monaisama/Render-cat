#include <functional>
#include "vecs/vec3.h"
#include "file.h"
#include "log.h"

#include "objects/text_object.h"

#include <iostream>
#include <string>
#include <array>
#include <any>
#include <optional>
#include <string_view>
#include <type_traits>

#include <concepts>

#include "patterns.h"

#include "test_header.h"

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

std::optional<std::string> TestOptional(bool bUse = true)
{
    if (bUse)
        return "string";
    return {};
}

int32_t operator""km(uint64_t value)
{
    return static_cast<int32_t>(value * 1000);
}

float_t operator""km(long double value)
{
    return value * 1000;
}

template<class T, size_t N>
size_t Size(const T(&)[N])
{
    return N;
}

// class Noncopyable
// {
// public:
//     Noncopyable(const Noncopyable&) = delete;
//     Noncopyable& operator=(const Noncopyable&) = delete;
// };

// class Nonmoveable
// {
// public:
//     Nonmoveable(Nonmoveable&&) = delete;
//     Nonmoveable& operator=(Nonmoveable&&) = delete;
// };

// #define GEN_SINGLETON_CODE(Type) \
//     public: \
//         static Type& GetInstance() \
//         { \
//             static Type instance; \
//             return instance; \
//         } \
//         \
//     private: \
//         Type() = default; \

// template<class T>
// class TestSingleton : public Noncopyable, public Nonmoveable
// {
//     static_assert(std::is_copy_assignable_v<T> && std::is_move_assignable_v<T>,  "error: T need not assignable and moveable");
// public:
//     int32_t Number() const { return -100000; }
// };

// class Single : public TestSingleton<Single>
// {
//     GEN_SINGLETON_CODE(Single)
// };

class TestSingleTon final
{
    GEN_SINGLETON_CODE(TestSingleTon)

public:
    int32_t GetNumber() const { static int32_t counter{}; return counter++; }

    template<class T>
    // requires std::is_integral_v<T>
    void TemplateFunc(T p)
    {
        throw std::exception("error no support func.");
    }
};

template<>
void TestSingleTon::TemplateFunc(int32_t p)
{
    KLog::LogSimple(p);
}

template<>
void TestSingleTon::TemplateFunc(std::string p)
{
    KLog::LogSimple(p);
}

int main()
{
    // KLog::Log(Single::GetInstance().Number());

    tfunc<int32_t>(100);
    func();

    return 0;

    std::string_view sv1{"helloworld"};
    std::string s1{"helloworld."};

    std::string_view sv2{s1};
    KLog::LogSimple("string_view equals test.", sv1 == sv2);

    try
    {
        using namespace std::string_literals;
        TestSingleTon::GetInstance().TemplateFunc(100);
        TestSingleTon::GetInstance().TemplateFunc("hellotemplate"s);
        TestSingleTon::GetInstance().TemplateFunc(1.f);
    } catch(std::exception e)
    {
        KLog::LogSimple("error happens: ->", e.what());
    }

    return 0;

    int32_t counter = 100;
    while(counter--)
    {
        KLog::Log(TestSingleTon::GetInstance().GetNumber());
    }

    // TestSingleTon single(TestSingleTon::GetInstance());
    // TestSingleTon single(TestSingleTon{TestSingleTon::GetInstance()});

    using array_t = int32_t(&)[5];
    using array_p = int32_t(*)[5];
    int32_t arr[] = {1,2,3,4,6};
    array_t a1 = arr;
    array_p p1 = &arr;
    KLog::Log(Size(*p1));

    return 0;

    std::string_view sView;
    std::string ss;
    char* charptr = nullptr;
    {
        std::string str { "hello view" };
        sView = str;
        ss = str;
        charptr = const_cast<char*>(str.c_str());
    }
    // std::cout << sView.data();
    KLog::Log(sView.data());
    KLog::Log(charptr);
    KLog::Log(nullptr);
    KLog::Log(ss);
    // std::cout << charptr;
    KLog::Log("");

    KLog::Log(TestOptional(true).value_or("empty"));
    KLog::Log(TestOptional(false).value_or("empty"));

    using namespace std::string_literals;
    using namespace std::string_view_literals;
    // "hello"s

    KLog::LogSimple(12km, 12.01km);

    return 0;

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