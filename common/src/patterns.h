#pragma once

/*
* Add some design patterns, singleton etc..
*/

#define GEN_SINGLETON_CODE(TypeName) \
    public: \
        static TypeName& GetInstance() \
        { \
            static TypeName instance; \
            return instance; \
        } \
          \
        TypeName(const TypeName&) = delete; \
        TypeName(TypeName&&) = delete; \
        TypeName& operator=(const TypeName&) = delete; \
        TypeName& operator=(TypeName&&) = delete; \
    private: \
        TypeName() = default; \

namespace std // using std namespace;
{
    
template<class T>
inline constexpr bool is_std_array = false;

template<class T, std::size_t N>
inline constexpr bool is_std_array<std::array<T, N>> = true;

}