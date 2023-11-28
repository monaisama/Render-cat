#pragma once

#include <array>
#include <cstdint>
#include <concepts>

/*
* Add some design patterns, singleton etc..
*/

#define GEN_DEFAULT_CONTRUCTOR_CODE(TypeName) \
    public: \
        TypeName(const TypeName&) = default; \
        TypeName(TypeName&&) = default; \
        TypeName& operator=(const TypeName&) = default; \
        TypeName& operator=(TypeName&&) = default; \


#define GEN_DELETE_CONTRUCTOR_CODE(TypeName) \
    public: \
        TypeName(const TypeName&) = delete; \
        TypeName(TypeName&&) = delete; \
        TypeName& operator=(const TypeName&) = delete; \
        TypeName& operator=(TypeName&&) = delete; \


#define GEN_DEFAULT_CONTRUCTOR_CODE_DEFAULT(TypeName) \
    public: \
        TypeName() = default; \
        GEN_DEFAULT_CONTRUCTOR_CODE(TypeName) \


#define GEN_DELETE_CONTRUCTOR_CODE_DEFAULT(TypeName) \
    public: \
        TypeName() = default; \
        GEN_DELETE_CONTRUCTOR_CODE(TypeName) \


#define GEN_DELETE_CONTRUCTOR_CODE_DELETE(TypeName) \
    public: \
        TypeName() = delete; \
        GEN_DELETE_CONTRUCTOR_CODE(TypeName) \


#define GEN_DEFAULT_CONTRUCTOR_CODE_DELETE(TypeName) \
    public: \
        TypeName() = delete; \
        GEN_DEFAULT_CONTRUCTOR_CODE(TypeName) \


#define GEN_SINGLETON_CODE(TypeName) \
    public: \
        static TypeName& GetInstance() \
        { \
            static TypeName instance; \
            return instance; \
        } \
        GEN_DEFAULT_CONTRUCTOR_CODE(TypeName) \
    private: \
        TypeName() = default; \


namespace std // using std namespace;
{
    
template<class T>
inline constexpr bool is_std_array = false;

template<class T, std::size_t N>
inline constexpr bool is_std_array<std::array<T, N>> = true;

template<class T>
concept KReal = requires (T number) {
    std::is_arithmetic_v<T>;
};

}