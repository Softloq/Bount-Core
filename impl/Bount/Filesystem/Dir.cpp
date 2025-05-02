#include "Bount/Core/Precompiled.hpp"
#include "Bount/Filesystem/Dir.hpp"
#include <boost/filesystem.hpp>

import Bount.Filesystem.Dir;

namespace Bount::Filesystem
{
Dir::Dir(const Path& path) noexcept
{

}
Dir::Dir(Path&& path) noexcept
{

}

Bool Dir::exists() const noexcept
{
    return false;
}
void Dir::create() noexcept
{

}
void Dir::remove() noexcept
{

}
void Dir::change(const Path& path) noexcept
{

}

std::vector<File> Dir::files() const noexcept
{
    std::vector<File> vec;
    return vec;
}
std::vector<Dir>  Dir::subDirs() const noexcept
{
    std::vector<Dir> vec;
    return vec;
}
}
