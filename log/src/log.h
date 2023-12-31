#pragma once
#include "compile_header.h"
#include <iostream>
#include <string>
#include <sstream>
#include <array>
#include <functional>
#include <string_view>
#include <type_traits>

namespace KLog
{

template<class... Args>
void Log(const std::string& format, const Args&... args)
{
    std::array<std::function<void(std::stringstream&)>, sizeof...(Args)> params
    {
        [&args](std::stringstream& outs)
        {
            // 如果这里是nullptr, 直接输出会crash，需要做一个判定
            if constexpr (std::is_pointer_v<Args>) if (args == nullptr)
            {
                outs << nullptr;
                return;
            }
            outs << std::boolalpha << args << std::noboolalpha;
        }...
    };

    std::stringstream ret;
    int32_t index = format.find_first_of('{');
    int32_t offset = 0;
    while (index != -1)
    {
        int32_t backIndex = format.find_first_of('}', index);
        if (backIndex == -1 || (index != 0 && format[index - 1] == '\\'))
            break;
        int32_t count = backIndex - index - 1;
        if (count > 0)
        {
            int32_t paramIndex = std::stoi(format.substr(index + 1, count));
            ret << format.substr(offset, index - offset);
            std::invoke(params[paramIndex], ret);
        }
        else
            ret << format.substr(offset, backIndex - offset + 1);
        offset = backIndex + 1;
        index = format.find_first_of('{', offset);
    }
    ret << format.substr(offset);

    std::cout << ret.str() << std::endl;
}

template<class... Args>
void LogSimple(const Args&... args) // todo.. 这里怎么将函数名重载到Log
{
    (void) std::initializer_list {
        ([&args](){
            if constexpr (std::is_pointer<Args>::value) if (args == nullptr)
            {
                std::cout << nullptr << " ";
                return;
            }
            std::cout << std::boolalpha << args << std::noboolalpha << " ";
        }() ,0)...
    };
    std::cout << std::endl;
}

template<class... Args>
void LogSimpleError(const Args&... args)
{
    LogSimple("ERROR:", std::forward<const Args>(args)...);
}

template<class... Args>
void LogSimpleWarning(const Args&... args)
{
    LogSimple("WARNING:", std::forward<const Args>(args)...);
}

template<class TParam>
void Log(const TParam& p)
{
    LogSimple(p);
}

template<class... Args>
void LogError(const std::string& format, const Args&... args)
{
    std::cout << "ERROR: ";
    Log(format, std::forward<const Args>(args)...);
}

template<class... Args>
void LogWarning(const std::string& format, const Args&... args)
{
    std::cout << "WARNING: ";
    Log(format, std::forward<const Args>(args)...);
}

}