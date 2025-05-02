#include "Bount/Core/Precompiled.hpp"
#include "Bount/Filesystem/File.hpp"
#include <boost/filesystem.hpp>

import Bount.Filesystem.File;

using namespace Bount;

namespace Bount::Filesystem
{
File::File(const Path& path, Modes modes) noexcept
{

}
File::File(Path&& path, Modes modes) noexcept
{

}

void File::open(const Path& path, Modes modes) noexcept
{

}
void File::close() noexcept
{

}

Bool File::exists() const noexcept
{
    return false;
}
SizeT File::size() const noexcept
{
    return 0;
}

FileBuffer File::readBuf(SizeT byteCount) const noexcept
{
    return FileBuffer();
}
String File::readChars(SizeT charCount) const noexcept
{
    return "";
}
String File::readLines(SizeT lineCount) const noexcept
{
    return "";
}

void File::write(const FileBuffer& buffer) noexcept
{

}
void File::write(const String& content) noexcept
{

}
}

std::ostream& operator<<(std::ostream& os, const Filesystem::File& file)
{
    return os;
}
std::istream& operator>>(std::istream& is, Filesystem::File& file)
{
    return is;
}