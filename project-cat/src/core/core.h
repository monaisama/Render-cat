#pragma once

#include "GL/glew.h"
#include <string>
#include <iostream>
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

// 所有meta信息的基类
struct IMeta
{};

class KObject
{
public:
    virtual const IMeta* GetMeta() const { return nullptr; }

    ~KObject() { }
};

}
