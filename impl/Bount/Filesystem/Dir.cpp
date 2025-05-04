#include "Bount/Core/Precompiled.hpp"
#include "Bount/Filesystem/Dir.hpp"
#include <boost/filesystem.hpp>

import Bount.Filesystem.Dir;

namespace Bount::Filesystem
{
Dir::Dir(const Path& path) noexcept
: _path(path)
{

}

Bool Dir::exists() const noexcept
{
    return _path.isDir();
}
void Dir::create() noexcept
{
    boost::filesystem::create_directory(_path.toString());
}
void Dir::remove() noexcept
{
    if (_path.isDir())
    {
        boost::filesystem::remove(_path.toString());
    }
}
void Dir::change(const Path& path) noexcept
{
    _path = path;
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
