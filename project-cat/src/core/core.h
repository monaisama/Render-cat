#pragma once

#include "GL/glew.h"
#include <string>
#include <cstdint>
#include <vector>
#include <array>
#include <optional>
#include <string_view>
#include <functional>
#include <algorithm>
#include <type_traits>

namespace KCore
{

class KObject
{
public:
    virtual ~KObject() { }
};

}
