#include <Bount/Subsystem/Generic.hpp>

import Bount.Subsystem;

using namespace Bount;

// Describes the independent functionality of this subsystem.
class Example final : public Subsystem::Generic<Example>
{
    Example() noexcept = default;
    ~Example() noexcept = default;

public:
    friend class Subsystem::Generic<Example>;
    friend class Singleton::Generic<Example>;

    void onStartup() override
    {
        std::cout << "Started Example Subsystem" << std::endl;
    }
    void onShutdown() noexcept override
    {
        std::cout << "Shutdown Example Subsystem" << std::endl;
    } 
};

Example& Singleton::Generic<Example>::getInstance() noexcept { BOUNT_SINGLETON_GET_INSTANCE_IMPL(Example); }

int main(int argc, char* argv[])
{
    Example::getInstance().startup();
    Example::getInstance().shutdown();
    return 0;
}
