#include <Bount/Core/DesignPatterns.hpp>
#include <Bount/Core/Subsystem.hpp>
#include <iostream>

using namespace Bount;
using namespace Bount::DesignPattern;

// Describes the independent functionality of this subsystem.
class ExampleSubsystem_ final : public SubsystemBase<ExampleSubsystem_>
{
public:
    void onStartup() override
    {
        std::cout << "Started Example Subsystem" << std::endl;
    }
    void onShutdown() override
    {
        std::cout << "Shutdown Example Subsystem" << std::endl;
    }
};
// Properly extends the behavior to a Bount Framework Subsystem.
using ExampleSubsystem = Subsystem<ExampleSubsystem_>; // Use ExampleSubsystem throughout your codebase.

int main(int argc, char* argv[])
{
    ExampleSubsystem::getInstance().startup();
    ExampleSubsystem::getInstance().shutdown();
    return 0;
}