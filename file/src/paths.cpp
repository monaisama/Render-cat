#include "paths.h"
#include <filesystem>
#include <algorithm>
#include "log.h"

namespace KFileUtils
{
    std::string GetRootPath(std::filesystem::path path, const std::string& prefix)
    {
        while (path.has_relative_path())
        {
            if (path.filename() == prefix)
                return path.parent_path().generic_string();
            path = path.parent_path();
        }
        return "./";
    }

    KPaths::InnerPath::InnerPath(const std::string& prefix)
        : projectPath(GetRootPath(std::filesystem::current_path(), prefix)),
            resourcePath((std::filesystem::path{projectPath}/"resource").generic_string()),
            configPath((std::filesystem::path{resourcePath}/"config").generic_string())
    {
    }

    KPaths::InnerPath KPaths::inner {};

    std::string KPaths::ConcatPath(std::initializer_list<std::string> paths)
    {
        std::filesystem::path ret;
        for (auto& path : paths)
        {
            ret /= path;
        }
        return ret.generic_string();
    }
}