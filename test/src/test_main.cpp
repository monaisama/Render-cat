#include <functional>
#include "vec.h"
#include "file.h"
#include "log.h"
#include "matrix.h"

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
#define test_temp 0
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

int32_t operator""_km(uint64_t value)
{
    return static_cast<int32_t>(value * 1000);
}

float_t operator""_km(long double value)
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
    // KLog::Log(sView.data());
    // KLog::Log(charptr);
    KLog::Log(nullptr);
    KLog::Log(ss);
    // std::cout << charptr;
    KLog::Log("");

    KLog::Log(TestOptional(true).value_or("empty"));
    KLog::Log(TestOptional(false).value_or("empty"));

    using namespace std::string_literals;
    using namespace std::string_view_literals;
    // "hello"s

    KLog::LogSimple(12_km, 12.01_km);
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

    KLog::LogSimple(KVec3f::up, KVec3i::right);

    KVec2f c1 { 10, 10 }, c2 { 10, -10};
    KLog::LogSimple(
        "test for vec2 method: \n",
        c1 == c2,
        c1 == c1,
        c1 != c2,
        c1 ^ c2,
        c1 | c2,
        c1 * 10,
        c2 * 10,
        c1 + c2,
        -c1,
        KVec2f::Dot(c1, c2),
        // c1 *= 10,
        // c2 *= 10,
        c1 + c2,
        c1.Length(),
        c2.Length(),
        c1.SqrtLength(),
        c2.SqrtLength(),
        // c1.Normalize(),
        // c2.Normalize(),
        KVec2i{0,1} ^ KVec2i{1,0},
        KVec2i{1,0} ^ KVec2i{0,1},
        "\nend test vec2 method."
    );

    KLog::LogSimple(c1.Normalize(), c2.Normalize());

    KVec3i cf1 {-10, 10, 10}, cf2 {10, 10, 10};
    KLog::LogSimple(
        "test vec3 start: \n",
        cf1 == cf2,
        cf1 == cf1,
        cf1 != cf2,
        cf1 + cf2,
        cf1 - cf2,
        cf1 / 10,
        cf2 * 100.f,
        cf1 | cf2,
        KVec3i::Cross(cf1, cf2),
        cf1.Length(),
        cf2.SqrtLength(),
        KVec3i{0,0,1} ^ KVec3i{0,1,0},
        KVec3i{0,1,0} ^ KVec3i{0,0,1},
        "\ntest vec3 end."
    );

    KLog::LogSimple(Distance(cf1, cf2), Distance(c1, c2));

    KLog::LogSimple(cf1.Normalize(), cf2.Normalize());

    KLog::LogSimple(KMath::Distance(KVec3f{0,0,1}, KVec3f{1,0,0}), KMath::Distance(KVec2i{0,1}, KVec2i{1,0}));

    KLog::LogSimple(KMatrix3f::identity, KMatrix3i::zero);

    KLog::LogSimple(MakeRotateMatrix(KVec3f::up, 90));
    KLog::LogSimple(MakeRotateMatrix(KVec3f::up, -90));
    KLog::LogSimple(MakeRotateMatrix(KVec3f::right, 90));
    KLog::LogSimple(MakeRotateMatrix(KVec3f::forward, 90));

    KLog::LogSimple(
        "test matrix3x3 start: \n",
        KMatrix3f::identity.TransformVector(KVec3f { 1.f, 1.f, 1.f}),
        "\n",
        KMatrix3f::identity * MakeRotateMatrix(KVec3f::up, 90),
        "\ntest matrix3x3 end."
    );

    KLog::LogSimple(MakeRotateMatrix(45));
    KLog::LogSimple(MakeRotateMatrix(180));

    KLog::LogSimple(
        "test matrix2x2 start: \n",
        KMatrix2f::identity,
        MakeRotateMatrix(90).TransformVector(KVec2f::up),
        "\ntest matrix2x2 end."
    );

    KLog::LogSimple(KMatrix2f::identity * 10);
    KLog::LogSimple(KMatrix3i::identity * 100);

    KLog::LogSimple(MakeRotateMatrix(KVec3f::up, 90));
    KLog::LogSimple(MakeRotateMatrix(KVec3f::up, 90).Transpose());

    auto transMatrix = MakeScaleMatrix(KVec2f::up, 2) * MakeScaleMatrix(KVec2f::right, 2);

    KLog::LogSimple(transMatrix, transMatrix.Inverse());
    auto point = KVec2f {1, 1};
    KLog::LogSimple(point, transMatrix * point, transMatrix.Inverse() * (transMatrix * point));
    KLog::LogSimple(transMatrix * transMatrix.Inverse());

    KLog::LogSimple(point * KMatrix2f::identity, point * transMatrix * transMatrix.Inverse());

    auto point1 = KVec3f { 1, 1, 1 };
    auto transMatrix1 = /*MakeRotateMatrix(KVec3f::up, 45) */ MakeScaleMatrix(KVec3f{ 1, 1, 1 }, 2);
    KLog::LogSimple(point1);
    KLog::LogSimple(point1 * transMatrix1);
    KLog::LogSimple(point1 * transMatrix1 * transMatrix1.Inverse());

#endif

#if test_file

    std::string content = KFile::ReadFile("default.vs");

    KLog::Log(content);
    KLog::Log(KFileTest{}.Int());

#endif

    return 0;
}