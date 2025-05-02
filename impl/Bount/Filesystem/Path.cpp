#include "Bount/Core/Precompiled.hpp"
#include "Bount/Filesystem/Path.hpp"
#include <boost/filesystem.hpp>

import Bount.Filesystem.Path;

namespace Bount::Filesystem
{
Path::Path(const String& pathString) noexcept
{

}
Path::Path(String&& pathString) noexcept
{

}

Bool Path::exists() const noexcept
{
    return false;
}
Bool Path::isAbsolute() const noexcept
{
    return false;
}
Bool Path::isRelative() const noexcept
{
    return false;
}
Bool Path::isDir() const noexcept
{
    return false;
}
Bool Path::isFile() const noexcept
{
    return false;
}

String Path::filename() const noexcept
{
    return "";
}
String Path::ext() const noexcept
{
    return "";
}

void Path::append(const Path& path) noexcept
{

}
Path Path::operator/(const Path& path) const noexcept
{
    return Path();
}

void Path::normalize() noexcept
{
}

Path Path::parent() const noexcept
{
    return Path();
}
String Path::toString() const noexcept
{
    return "";
}
}