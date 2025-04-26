#include <Bount/Singleton/Generic.hpp>
#include <iostream>

import Bount.Singleton;

using namespace Bount;

// Describes the independent functionality of this singleton.
class Example final : public Singleton::Generic<Example>
{
    Example() = default;
    ~Example() = default;

public:
    friend class Singleton::Generic<Example>;

    void someFunction()
    {
        std::cout << "Example Singleton: Some Function" << std::endl;
    }  
};

Example& Singleton::Generic<Example>::getInstance() noexcept { BOUNT_SINGLETON_GET_INSTANCE_IMPL(Example); }

int main(int argc, char* argv[])
{
    Example::getInstance().someFunction();
    return 0;
}
