#include <Bount/Core/DesignPatterns.hpp>
#include <iostream>

using namespace Bount;
using namespace Bount::DesignPattern;

// Describes the independent functionality of this singleton.
class ExampleSingleton_ final : public SingletonBase<ExampleSingleton_>
{
public:
    void someFunction()
    {
        std::cout << "Example Singleton: Some Function" << std::endl;
    }
};
// Properly extends the behavior to a Bount Framework Singleton.
using ExampleSingleton = Singleton<ExampleSingleton_>; // Use ExampleSingleton throughout your codebase.

int main(int argc, char* argv[])
{
    ExampleSingleton::getInstance().someFunction();
    return 0;
}