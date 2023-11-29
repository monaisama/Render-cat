#pragma once
#include "compile_header.h"
#include <string>
#include <filesystem>

namespace KFileUtils
{

class K_API KPaths final
{
    class InnerPath
    {
    public:
        const std::string projectPath;
        const std::string resourcePath;
        const std::string configPath;

        InnerPath(const std::string& prefix = "build");
    };
public:
    static const std::string& ProjectPath() { return inner.projectPath; }
    static const std::string& ResourcePath() { return inner.resourcePath; }

    static std::string ConfigPath(const std::string& file = "") { return (std::filesystem::path{inner.configPath}/file).generic_string(); }
    static std::string ShaderPath(const std::string& file = "") { return (std::filesystem::path{inner.resourcePath}/"shader"/file).generic_string(); }
    static std::string TexturePath(const std::string& file = "") { return (std::filesystem::path{inner.resourcePath}/"texture"/file).generic_string(); }

    static std::string ConcatPath(std::initializer_list<std::string>);

    template<class... TArgs>
    requires std::same_as<std::string, TArgs...>
    static std::string ConcatPath(const TArgs&... args)
    {
        ConcatPath({args...});
    }

private:
    static InnerPath inner;
};

}