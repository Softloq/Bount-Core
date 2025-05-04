#include "Bount/Core/Precompiled.hpp"
#include "Bount/Filesystem/File.hpp"
#include <boost/filesystem.hpp>

import Bount.Filesystem.File;

using namespace Bount;

namespace Bount::Filesystem
{
File::File(const Path& path, Modes modes) noexcept
: _path(path)
{
    open(modes);
}
File::File(Path&& path, Modes modes) noexcept
: _path(std::move(path))
{
    open(modes);
}

void File::open(const Path& path, Modes modes) noexcept
{
    _path = path;
    open(modes);
}
void File::open(Modes modes) noexcept
{
    std::ios_base::openmode mode = 0;
    if (static_cast<Signed>(modes) & static_cast<Signed>(Modes::Read))
    {
        mode |= std::ios_base::out;
    }
    else if (static_cast<Signed>(modes) & static_cast<Signed>(Modes::Write))
    {
        mode |= std::ios_base::in | std::ios_base::trunc;
    }
    else if (static_cast<Signed>(modes) & static_cast<Signed>(Modes::Append))
    {
        mode |= std::ios_base::in | std::ios_base::app;
    }
    else if (static_cast<Signed>(modes) & static_cast<Signed>(Modes::Binary))
    {
        mode |= std::ios_base::binary;
    }
    _file = std::make_shared<std::fstream>(_path.toString().c_str(), mode);
}
void File::close() noexcept
{
    if (_file)
    {
        _file.reset();
    }
}

Bool File::exists() const noexcept
{
    return _path.isFile();
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