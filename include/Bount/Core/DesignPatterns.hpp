/**
 * @file DesignPatterns.hpp
 * @brief Standard Software Design Patterns sublibrary.
 * @author Brandon Foster (Paradox Gene)
 */

#ifndef BOUNT_CORE_DESIGN_PATTERNS_HPP
#define BOUNT_CORE_DESIGN_PATTERNS_HPP

#include "Bount/Core/Datatypes.hpp"
#include <mutex>
#include <typeinfo>
#include <iostream>

namespace Bount::DesignPattern
{
/** @brief
 * Abstract class for creating concrete singletons.
 * All singletons must inherit from this class to operate properly within the Bount Framework.
 */
template <typename T>
class SingletonBase
{
public:
    static int _instanceCount;

    SingletonBase() noexcept { increment(); }
    SingletonBase(const SingletonBase&) noexcept { increment(); }
    SingletonBase(SingletonBase&&) noexcept { increment(); }
    SingletonBase& operator=(const SingletonBase&) noexcept { increment(); return *this; }
    SingletonBase& operator=(SingletonBase&&) noexcept { increment(); return *this; }

    virtual ~SingletonBase() = 0;

private:
    void increment() noexcept
    {
        static std::mutex mtx;
        std::lock_guard<std::mutex> lock(mtx);
        if (!_instanceCount++) return;

        String id = typeid(T).name();
        String error_msg = String("Only one instance of ") + id + " is allowed";
        std::cerr << "Assertion failed: " << error_msg << ", file " << __FILE__ << ", line " << __LINE__ << std::endl;
        std::abort();
    }
};
template <typename T>
int SingletonBase<T>::_instanceCount = 0;
template <typename T>
SingletonBase<T>::~SingletonBase() {}

/** @brief Final behavior extension for a singleton.*/
template <typename T>
class Singleton
{
public:
    Singleton(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton& operator=(Singleton&&) = delete;

    static T& getInstance() noexcept
    {
        static std::unique_ptr<T> instance;
        static std::once_flag init;
        std::call_once(init, []()
        {
            instance.reset(new T);
        });
        return *instance;
    }

private:
    Singleton() noexcept = default;
    ~Singleton() noexcept = default;
};
}

#endif