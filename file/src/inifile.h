#pragma once

#include "compile_header.h"
#include "patterns.h"
#include <string>
#include <string_view>
#include <map>
#include <utility>
#include <optional>
#include <vector>
#include <ranges>

namespace KFileUtils
{

class K_API KIniFile final
{
    GEN_DEFAULT_CONTRUCTOR_CODE(KIniFile)
public:
    static const std::string defaultSection;

    using SectionType = std::string;
    using ConfigValueType = std::map<std::string, std::string>;

    KIniFile();
    KIniFile(const std::string& content);
    KIniFile(std::string_view filepath);

    void Write(std::string_view filepath);
    void Write();

    static KIniFile Open(std::string_view filepath);

    void SetConfig(const std::string& section, const std::string& key, const std::string& value);
    std::optional<std::string_view> GetConfig(const std::string& section, const std::string& key) const;
    const ConfigValueType& GetConfig(const std::string& section) const;

    const std::map<SectionType, ConfigValueType>& GetConfig() const;

private:
    void ParseContent(const std::string& content);
    std::optional<std::pair<std::string, std::optional<std::string>>>
        ParseLine(std::string_view line);

private:
    std::string filePath;
    std::map<SectionType, ConfigValueType> values;
};

}