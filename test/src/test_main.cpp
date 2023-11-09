#include <functional>
#include "vec.h"
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

#define test_cxxfeature 0
#define test_math 1
#define test_file 0
#define test_log 0
#define test_initializelist 0
#define test_temp 1
#define test_arraytype 0
#define test_stringview 0
#define test_singleton 0

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
#if test_temp
    // tfunc<int32_t>(100);
    // func();
#endif

#if test_singleton
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

    int32_t counter = 100;
    while(counter--)
    {
        KLog::Log(TestSingleTon::GetInstance().GetNumber());
    }

    // TestSingleTon single(TestSingleTon::GetInstance());
    // TestSingleTon single(TestSingleTon{TestSingleTon::GetInstance()});
#endif

#if test_arraytype
    using array_t = int32_t(&)[5];
    using array_p = int32_t(*)[5];
    int32_t arr[] = {1,2,3,4,6};
    array_t a1 = arr;
    array_p p1 = &arr;
    KLog::Log(Size(*p1));
#endif

#if test_stringview
    std::string_view sv1{"helloworld"};
    std::string s1{"helloworld."};

    std::string_view sv2{s1};
    KLog::LogSimple("string_view equals test.", sv1 == sv2);

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
#endif

#if test_log
    KLog::Log("failed");
    KLog::LogError("error");
    KLog::LogError("start {0} - {1} middle\{} {0} {2} bool {3} logend", -1, 100.1f, "hello log", true);

    KLog::Log(std::is_std_array<std::array<int32_t, 10>>);
#endif

#if test_cxxfeature
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
#endif

#if test_math
    KVec3f vec1{}, vec2(1.f, 2.f, 3.f);

    vec1 += vec2;
    std::cout << vec1.X() << " " << vec1.Y() << " " << vec1.Z() << std::endl;

    KVec4 vec(1.f, 1.f, 1.f, 2.f);
    KLog::LogSimple(vec.XYZW()[0], vec.XYZW()[1], vec.XYZW()[2], vec.XYZW()[3]);

    KVec2f c21 { 100.1f, -10.2f};
    KLog::LogSimple(c21.X(), c21.Y());
    KLog::LogSimple(KVec2f::up.X(), KVec2f::up.Y());

    KLog::LogSimple(KVec2i::right.X(), KVec2i::right.Y());

    // KLog::LogSimple(KVec2hi::Up.X(), KVec2hi::Right.Y());

    KVec2i c1 { 1, 1 }, c2 { 1, -1};
    KVec2i c3 = c1 ^ c2;
    std::cout << c3 << c1 << c2;
    KLog::LogSimple(c1 | c2);
    KLog::LogSimple(
        "test for vec2 method: \n",
        c1 == c2,
        c1 != c2,
        c1 ^ c1,
        c1 | c2,
        c1 * 10,
        c2 * 10,
        c1 + c2,
        c1 *= 10,
        c2 *= 10,
        c1 + c2,
        c1.Length(),
        c2.Length(),
        c1.SqrtLength(),
        c2.SqrtLength(),
        c1.Normalize(),
        c2.Normalize(),
        "\nend test vec2 method."
    );

#endif

#if test_file

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
#endif

    return 0;
}