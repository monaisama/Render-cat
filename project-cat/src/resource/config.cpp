#include "config.h"
#include "inifile.h"
#include <string_view>
#include "paths.h"

namespace KCore
{

using namespace KFileUtils;

const std::string KConfig::defaultIniPath{"default.ini"};
const std::string KConfig::cameraSectionName{"camera"};
const std::string KConfig::screenSectionName{"screen"};

void KConfig::InitFromDefaultConfig()
{
    defaultIni.Read(KPaths::ConfigPath(defaultIniPath));
}

template std::string KConfig::GetValue<std::string>(const std::string& section, const std::string& key);
template std::string_view KConfig::GetValue<std::string_view>(const std::string& section, const std::string& key);
template int32_t KConfig::GetValue<int32_t>(const std::string& section, const std::string& key);
template bool KConfig::GetValue<bool>(const std::string& section, const std::string& key);
template float KConfig::GetValue<float>(const std::string& section, const std::string& key);

}
