#ifndef BOUNT_SINGLETON_GENERIC_HPP
#define BOUNT_SINGLETON_GENERIC_HPP

#include "Bount/Core/Datatypes.hpp"

#define BOUNT_SINGLETON_GET_INSTANCE_IMPL(CLASS)\
    using singleton_class = CLASS;\
    static singleton_class* instance;\
    static std::once_flag init;\
    std::call_once(init, []() { instance = new singleton_class; });\
    return *instance;
#endif
