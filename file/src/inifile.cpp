#include "file.h"
#include "inifile.h"
#include <sstream>
#include <filesystem>
#include <algorithm>
#include <functional>
#include "log.h"
#include <ranges>

namespace KFileUtils
{

using std::string_literals::operator""s;
const std::string KIniFile::defaultSection{"default"s};

KIniFile::KIniFile()
    : filePath{}, values{}
{
}

KIniFile::KIniFile(const std::string& content)
    : KIniFile()
{
    ParseContent(content);
}

KIniFile::KIniFile(std::string_view filepath)
    : filePath{filepath}, values{}
{
    ParseContent(KFile::ReadFile(filepath));
}

void KIniFile::ParseContent(const std::string& content)
{
    std::stringstream stream(content);
    std::string line;

    struct
    {
        std::string curSection = defaultSection;
    } context;

    while (std::getline(stream, line))
    {
        if (auto pair = ParseLine(line); pair) // 不是注释或者空行
        {
            auto value = pair.value();
            if (!value.second) // 新的section配置
            {
                context.curSection = value.first;
            }
            else // 真正的配置
            {
                SetConfig(context.curSection, value.first, value.second.value());
            }
        }
    }
}

void KIniFile::Write(std::string_view filepath)
{
    if (filepath.empty())
    {
        KLog::LogWarning("invalid ini file path {0}", filepath);
        return;
    }
    namespace fs = std::filesystem;
    auto path = fs::path{filepath};
    if (path.has_parent_path() && !fs::exists(path.parent_path()))
        fs::create_directory(path.parent_path());

    KFile file = KFile::OpenFile(filepath);
    auto writeConfig = [&file](const ConfigValueType& value)
    {
        if (value.size() == 0) return;
        for (auto& pair : value)
        {
            file.GetStream() << pair.first << "=" << pair.second << "\n";
        }
        file.GetStream() << std::endl;
    };
    writeConfig(GetConfig(defaultSection));
    std::string curSection = defaultSection;
    for (const auto& value : values)
    {
        if (value.first == defaultSection) continue;
        if (value.first != curSection)
        {
            curSection = value.first;
            file.GetStream() << "[" << value.first << "]\n";
        }
        writeConfig(value.second);
    }
}

void KIniFile::Write()
{
    Write(filePath);
}

KIniFile KIniFile::Open(std::string_view filepath)
{
    return KIniFile(filepath);
}

void KIniFile::SetConfig(const std::string& section, const std::string& key, const std::string& value)
{
    if (auto it = values.find(section); it == values.end())
    {
        values[section] = ConfigValueType{};
    }
    values[section][key] = value;
}

std::optional<std::string_view> KIniFile::GetConfig(const std::string& section, const std::string& key) const
{
    if (auto it = values.find(section); it != values.end())
    {
        if (auto valueit = it->second.find(key); valueit != it->second.end())
            return valueit->second;
    }
    return {};
}

const KIniFile::ConfigValueType& KIniFile::GetConfig(const std::string& section) const
{
    if (auto it = values.find(section); it != values.end())
        return it->second;
    return ConfigValueType{};
}

const std::map<KIniFile::SectionType, KIniFile::ConfigValueType>& KIniFile::GetConfig() const
{
    return values;
}

std::optional<std::pair<std::string, std::optional<std::string>>> KIniFile::ParseLine(std::string_view line)
{
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

    // 补充标准库中的string方法
    auto trim = [](std::string_view s)
    {
        std::string str{s};
        str.erase(str.begin(), std::find_if_not(str.begin(), str.end(), [](char c) { return std::isspace(c); }));
        str.erase(std::find_if_not(str.rbegin(), str.rend(), [](char c) { return std::isspace(c); }).base(), str.end());
        return str;
    };

    auto split = remove(line, "//") |
        std::views::split('=') |
        std::views::transform([](auto&& rng) { return std::string_view(&*rng.begin(), std::ranges::distance(rng)); });
    
    std::size_t count = std::ranges::distance(split);
    if (count == 0)
        return {};
    else if (count == 2)
        return std::pair{trim(*split.begin()), trim(*(++split.begin()))};
    else if (count == 1) // check section
    {
        std::string_view section = *split.begin();
        KLog::LogSimple("section: ", section);
        if (section.find_first_of("[") != std::string_view::npos && section.find_first_of("]") != std::string_view::npos)
        {
            section = remove(remove(section, "[", false), "]");
            if (auto str = trim(section); str.size() != 0)
            {
                KLog::LogSimple("after section: ", str);
                return std::pair<std::string, std::optional<std::string>>{std::move(str), {}};
            }
        }
    }
    KLog::LogError("ill-format ini file: {0} {1}", filePath, line);
    return {};
}

}