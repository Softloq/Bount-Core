module;

#include "Bount/Singleton/Generic.hpp"

export module Bount.Singleton;
export namespace Bount::Singleton
{
/** @brief
 * Abstract template class for creating concrete singletons.
 * All singletons must inherit from this class to operate properly within the Bount Framework.
 */
template <typename T>
class Generic
{
    Generic(const Generic&) = delete;
    Generic& operator=(const Generic&) = delete;

public:
    static T& getInstance() noexcept;

protected:
    Generic() noexcept = default;
    ~Generic() noexcept = default;
};
}
