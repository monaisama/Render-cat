#include <functional>
#include "vec.h"
#include "file.h"
#include "log.h"
#include "matrix.h"
#include "camera.h"
#include "transform/transform.h"

#include <iostream>
#include <string>
#include <array>
#include <any>
#include <optional>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>
#include <set>
#include <map>
#include <tuple>

#include <concepts>
#include <ranges>
#include <filesystem>

#include "patterns.h"

#include "test_header.h"
#include "inifile.h"
#include "paths.h"

using namespace KMath;
using namespace KFileUtils;

#define test_cxxfeature 0
#define test_math 0
#define test_file 1
#define test_log 0
#define test_initializelist 0
#define test_temp 0
#define test_arraytype 0
#define test_stringview 0
#define test_singleton 0
#define calc_coding_line 1

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

template<std::KReal real1, std::KReal real2>
requires std::is_floating_point_v<real1> && std::is_floating_point_v<real2>
void AddFunc(real1 n1, real2 n2)
{
    // static_assert(std::same_as<real1, float>, "must be float");
    KLog::LogSimple("test real ", n1 + n2);
}

template<std::KInteger int1, std::KInteger int2>
void AddFunc(int1 n1, int2 n2)
{
    KLog::LogSimple("test integer ", n1 + n2);
}

int main()
{
#if test_temp
{
    namespace fs = std::filesystem;
    using namespace std::string_view_literals;
    KLog::LogSimple(fs::current_path());
    auto cur = fs::current_path();

    while (cur.has_relative_path())
    {
        KLog::LogSimple(cur = cur.parent_path());
        KLog::LogSimple(cur.filename());
    }
}
#endif

#if calc_coding_line
{
    namespace fs = std::filesystem;
    using namespace KFileUtils;
    struct
    {
        std::string_view operator()(std::string_view s, std::string_view sep, bool bReverse = true)
        {
            if (auto pos = s.find_first_of(sep); pos != std::string_view::npos)
            {
                if (bReverse)
                {
                    auto temp = s |
                        std::views::reverse |
                        std::views::drop(s.length() - pos) |
                        std::views::reverse;
                    return std::string_view(&*temp.begin(), std::ranges::distance(temp));
                }
                else
                {
                    auto temp = s |
                        std::views::drop(pos + 1);
                    return std::string_view(&*temp.begin(), std::ranges::distance(temp));
                }
            }
            return s;
        }
    } remove;

    bool bComment = false;

    // 补充标准库中的string方法
    auto trim = [](std::string_view s)
    {
        std::string str{s};
        str.erase(str.begin(), std::find_if_not(str.begin(), str.end(), [](char c) { return std::isspace(c); }));
        str.erase(std::find_if_not(str.rbegin(), str.rend(), [](char c) { return std::isspace(c); }).base(), str.end());
        return str;
    };

    auto parseLine = [bComment, &trim, &remove](std::string_view line) -> int32_t
    {
        if (!bComment)
            line = remove(line, "//"); // 不管 /**/ 了
        auto str = trim(line);
        if (str == "")
            return 0;
        return 1;
    };
    
    auto calcSingleFile = [&parseLine](fs::path& path) -> int32_t
    {
        std::string content = KFile::ReadFile(path.generic_string());
        std::stringstream ss(content);
        std::string line;
        int32_t num = 0;
        while (std::getline(ss, line))
        {
            num += parseLine(line);
        }
        return num;
    };

    std::vector<std::string> folders { "common", "file", "log", "physics", "project-cat", "test" };
    std::set<std::string> ext { ".h", ".cpp" };
    auto calc = [&ext, &calcSingleFile](const std::string& inFolder)
    {
        std::string path = KPaths::ConcatPath({KPaths::ProjectPath(), inFolder});
        int32_t filecount = 0, linecount = 0;
        for (fs::directory_entry entry : fs::recursive_directory_iterator(fs::path{path}))
        {
            if (!entry.is_regular_file()) continue;
            if (auto fp = entry.path(); fp.has_extension())
            {
                if (auto it = ext.find(fp.extension().generic_string()); it != ext.end())
                {
                    ++filecount;
                    linecount += calcSingleFile(fp);
                }
            }
        }
        return std::tuple<int32_t, int32_t>(filecount, linecount);
    };

    int32_t filecount = 0, linecount = 0;
    for (auto& folder : folders)
    {
        auto counter = calc(folder);
        KLog::Log("start calc folder: |{0}|, files: {1}, lines: {2}", folder, std::get<0>(counter), std::get<1>(counter));
        filecount += std::get<0>(counter);
        linecount += std::get<1>(counter);
    }
    KLog::Log("total files: {0}, lines: {1}\n", filecount, linecount);
}
#endif

#if test_file
{
    std::string content1 = KFile::ReadFile("default.vs");
    KLog::Log(content1);

    using namespace std::string_view_literals;
    using namespace std::string_literals;
    // tfunc<int32_t>(100);
    // func();

    auto filepath = "test_ini.txt"sv;
    namespace fs = std::filesystem;
    if (!fs::exists(fs::path{filepath}))
    {
        KIniFile file;
        file.SetConfig(KIniFile::defaultSection, "test1", std::to_string(100));
        file.SetConfig("test_section", "test1", "testttt");

        file.Write(filepath);
    }

    std::string configPath = KPaths::ConfigPath("default.ini"s);
    if (!fs::exists(fs::path{configPath}))
    {
        KIniFile file;
        file.SetConfig("screen", "width", std::to_string(800));
        file.SetConfig("screen", "height", std::to_string(600));
        file.SetConfig("camera", "fov", "90");
        file.SetConfig("camera", "speed", "2.5");
        file.SetConfig("camera", "sensitivity", "0.01");

        file.Write(configPath);
    }

    KIniFile file1(filepath);
    for (auto& pair : file1.GetConfig(KIniFile::defaultSection))
    {
        KLog::LogSimple(pair.first, pair.second);
    }

    // using namespace std::string_literals;
    // std::stringstream ss("helloworld\nhelloc++"s);
    // std::string line;
    // while (std::getline(ss, line))
    // {
    //     KLog::LogSimple("line: ", line);
    // }
    std::string content = KFile::ReadFile(filepath);
    // KLog::LogSimple("read file\n", content);
    KIniFile ini(content);
    for (auto key : std::views::keys(ini.GetConfig()))
    {
        KLog::LogSimple("key: ", key);
    }

    std::string_view line = "hello=world//cc"sv;
    if (auto pos = line.find_first_of("//"); pos != std::string_view::npos)
    {
        auto temp = line |
            std::views::reverse |
            std::views::drop(line.length() - pos) |
            std::views::reverse;
        line = std::string_view (&*temp.begin(), std::ranges::distance(temp));
    }
    auto split = line |
        // std::ranges::views::reverse |
        // std::ranges::views::drop(line.length() - line.find_first_of("//")) | // remove comment
        // std::ranges::views::reverse |
        std::ranges::views::split('=') |
        std::ranges::views::transform([](auto&& rng) { return std::string_view(&*rng.begin(), std::ranges::distance(rng)); });
    // for (auto sp : split)
    // {
    //     KLog::LogSimple("split: ", sp);
    // }

    KLog::LogSimple(KPaths::ProjectPath(), KPaths::ResourcePath(), KPaths::ConfigPath());
    KLog::LogSimple("start test path\n",
        KPaths::ConcatPath({KPaths::ProjectPath(), "file.cpp"}),
        "\nend test path.");
}
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
{
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

    using namespace std::string_view_literals;
    using namespace std::string_literals;

    constexpr auto sv1 { "string=split_//_comment=none"sv };
    auto splitStr = sv1 |
        std::views::reverse |
        std::views::drop(sv1.length() - sv1.find_first_of("//")) |
        std::views::reverse |
        std::views::split('=') |
        std::views::transform([](auto&& rng) -> std::string_view { return std::string_view(&*rng.begin(), std::ranges::distance(rng)); });
    for (auto s : splitStr)
    {
        KLog::LogSimple(s);
    }

    AddFunc(1.f, 2.f);
    AddFunc(1, 0);

    AddFunc(-1, 10);
}

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
        c1 * c2,
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
        cf1 * cf2,
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

    KLog::LogSimple(KVec4f::wzero, KVec4f::wzero * MakeTranslateMatrix(point1));
    KLog::LogSimple(KVec3f::wzero, ToVec2<float>(KVec3f::wzero * MakeTranslateMatrix(KVec2f{1,1})));

    KMatrix4f transMatrix2 = MakeTranslateMatrix(KVec3f {-1,1,1});
    KVec3f point2 {1,0,0};
    KLog::LogSimple(transMatrix2, transMatrix2.Inverse());
    KLog::LogSimple(point2, point2 * transMatrix2, point2 * transMatrix2 * transMatrix2.Inverse());

    KMatrix3f transMatrix3 = MakeTranslateMatrix(KVec2f {-1,1});
    KVec2f point3 {1,0};
    KLog::LogSimple(point3, point3 * transMatrix3, point3 * transMatrix3 * transMatrix3.Inverse());

    KMatrix4i transMatrix4 = MakeTranslateMatrix<int32_t>(KVec3i {-1,1,1});
    KVec3i point4 {1,0,0};
    KLog::LogSimple(transMatrix4, transMatrix4.Inverse());
    KLog::LogSimple(point4, point4 * transMatrix4, point4 * transMatrix4 * transMatrix4.Inverse());

    KMatrix3i transMatrix5 = MakeTranslateMatrix<int32_t>(KVec2i {-1,1});
    KVec2i point5 {1,0};
    KLog::LogSimple(point5, point5 * transMatrix5, point5 * transMatrix5 * transMatrix5.Inverse());

    KCamera camera = KCamera::Ortho(1.f, 10.f, 80, 60).LookAt({-5,0,0}, KVec3f::zero);
    KMatrix4f MVP = camera.Matrix();
    
    // 0, -1, -1,
    // 0, 1, -1,
    // 0, 0, 1,
    KVec3f a {0, -1, -1}, b {0, 1, -1}, c {0, 0, 1};

    KCamera perspCam = KCamera::Persp(90, 0.1f, 100.f, 8.f / 6.f).LookAt({-5,0,0}, KVec3f::zero);
    
    KLog::LogSimple(
        "start MVP test:\n",
        // camera.ProjectiveMatrix(),
        camera.ViewMatrix(),
        a * camera.ViewMatrix(),
        b * camera.ViewMatrix(),
        c * camera.ViewMatrix(),
        a * MVP,
        b * MVP,
        c * MVP,
        "\nend mvp test.");

    KVec4f a4f {0, -1, -1, 1}, b4f {0, 1, -1, 1}, c4f {0, 0, 1, 1};
    KLog::LogSimple(
        "start persp test:\n",
        perspCam.ViewMatrix(),
        a4f * perspCam.ViewMatrix(),
        b4f * perspCam.ViewMatrix(),
        c4f * perspCam.ViewMatrix(),
        "\n",
        perspCam.Matrix(),
        a4f * perspCam.Matrix(),
        b4f * perspCam.Matrix(),
        c4f * perspCam.Matrix(),
        "\nend persp test.");

    auto ShowLocation = [](KCameraTransformer& transformer)
    {
        KLog::Log("location ({0})", transformer.GetCameta().ViewMatrix().Inverse() * KVec3f::zero);
    };

    KLog::LogSimple("Start camera transformer:");
    KCameraTransformer transformer(KCamera::Persp(90.f, 0.1, 100.f, 1).LookAt({-5,3,6}, KVec3f::zero));
    ShowLocation(transformer);
    transformer.MoveForward(5.f);
    ShowLocation(transformer);
    transformer.MoveRight(-3.f);
    ShowLocation(transformer);

    transformer.MoveThenLookAt({0,0,4}, KVec3f::zero);
    ShowLocation(transformer);
    
    KLog::LogSimple("End camera transformer:\n");

#endif

    return 0;
}