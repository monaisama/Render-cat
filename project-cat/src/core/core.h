#pragma once

#include "GL/glew.h"
#include <string>
#include <iostream>
#include <cstdint>
#include <vector>
#include <array>

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
