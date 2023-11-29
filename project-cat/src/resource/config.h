#pragma once

#include "patterns.h"
#include <string>
#include <exception>
#include <memory>
#include "inifile.h"

namespace KCore
{

class KConfig final
{
    GEN_SINGLETON_CODE(KConfig)
public:
    static const std::string defaultIniPath;
    static const std::string cameraSectionName;
    static const std::string screenSectionName;

public:
    void InitFromDefaultConfig();

    template<class TValue>
    TValue GetValue(const std::string& section, const std::string& key)
    {
        throw std::exception("not support type.");
    }

    template<class TValue> requires std::is_integral_v<TValue>
    TValue GetValue(const std::string& section, const std::string& key)
    {
        std::string value = GetValue<std::string>(section, key);
        if (value == "")
            return static_cast<TValue>(0);
        return static_cast<TValue>(std::stoi(value));
    }

    template<class TValue> requires std::is_floating_point_v<TValue>
    TValue GetValue(const std::string& section, const std::string& key)
    {
        std::string value = GetValue<std::string>(section, key);
        if (value == "")
            return static_cast<TValue>(0);
        return static_cast<TValue>(std::stof(value));
    }

    template<> std::string GetValue(const std::string& section, const std::string& key)
    {
        auto value = defaultIni.GetConfig(section, key);
        if (value.has_value())
            return std::string{value.value()};
        return {};
    }

    template<> std::string_view GetValue(const std::string& section, const std::string& key)
    {
        auto value = defaultIni.GetConfig(section, key);
        if (value.has_value())
            return value.value();
        return std::string_view{};
    }

private:
    KFileUtils::KIniFile defaultIni;
};

}