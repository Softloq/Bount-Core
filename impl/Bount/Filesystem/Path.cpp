#include "Bount/Core/Precompiled.hpp"
#include "Bount/Filesystem/Path.hpp"
#include <boost/filesystem.hpp>

#if defined(BOUNT_WINDOWS)
    #include <windows.h> // For GetModuleFileNameA
#elif defined(BOUNT_LINUX)
    #include <limits.h> // For PATH_MAX
    #include <unistd.h> // For readlink
#endif

import Bount.Filesystem.Path;

namespace Bount::Filesystem
{
Path::Path(const String& path) noexcept
: _path(path)
{
}
Path::Path(String&& path) noexcept
: _path(std::move(path))
{
}

void Path::append(const Path& path) noexcept
{
    _path /= path._path;
}
Path& Path::operator/=(const Path& path) noexcept
{
    _path /= path._path;
    return *this;
}

void Path::concat(const Path& path) noexcept
{
    _path += path._path;
}
Path& Path::operator+=(const Path& path) noexcept
{
    _path += path._path;
    return *this;
}

Bool Path::isAbsolute() const noexcept
{
    return _path.is_absolute();
}
Bool Path::isRelative() const noexcept
{
    return _path.is_relative();
}
Bool Path::isFile() const noexcept
{
    return boost::filesystem::is_regular_file(_path);
}
Bool Path::isDir() const noexcept
{
    return boost::filesystem::is_directory(_path);
}
Bool Path::exists() const noexcept
{
    return boost::filesystem::exists(_path);
}

Path Path::absolute() const noexcept
{
    Path absPath;
    absPath._path = boost::filesystem::absolute(_path, exeDir()._path);
    return absPath;
}
Path Path::relative(const Path& path) const noexcept
{
    Path relPath;
    relPath._path = boost::filesystem::relative(_path, path._path);
    return relPath;
}
Path Path::canonical() const noexcept
{
    Path canonPath;
    canonPath._path = boost::filesystem::canonical(_path, exeDir()._path);
    return canonPath;
}
Path Path::normalize() const noexcept
{
    Path normalPath;
    normalPath._path = _path.lexically_normal();
    return normalPath;
}

Bool Path::hasFilename() const noexcept
{
    return _path.has_filename();
}
Bool Path::hasExtension() const noexcept
{
    return _path.has_extension();
}
Bool Path::hasStem() const noexcept
{
    return _path.has_stem();
}
Bool Path::hasParent() const noexcept
{
    return _path.has_parent_path();
}

Path Path::filename() const noexcept
{
    Path filenamePath;
    filenamePath._path = _path.filename();
    return filenamePath;
}
Path Path::extension() const noexcept
{
    Path extensionPath;
    extensionPath._path = _path.extension();
    return extensionPath;
}
Path Path::stem() const noexcept
{
    Path stemPath;
    stemPath._path = _path.stem();
    return stemPath;
}
Path Path::parent() const noexcept
{
    Path parentPath;
    parentPath._path = _path.parent_path();
    return parentPath;
}

String Path::toString() const noexcept
{
    return _path.string();
}

Path operator/(const Path& lhs, const Path& rhs) noexcept
{
    Path appendPath = lhs;
    appendPath._path /= rhs._path;
    return appendPath;
}
Path operator+(const Path& lhs, const Path& rhs) noexcept
{
    Path concatPath = lhs;
    concatPath._path += rhs._path;
    return concatPath;
}

const Path& Path::exeFile() noexcept
{
    static Path exeFilePath;
    static std::once_flag initFlag;
    std::call_once(initFlag, []()
    {
    #if defined(BOUNT_WINDOWS)
        char buffer[MAX_PATH];
        GetModuleFileNameA(NULL, buffer, MAX_PATH);
    #elif defined(BOUNT_LINUX)
        char buffer[PATH_MAX];
        ssize_t count = readlink("/proc/self/exe", buffer, PATH_MAX);
    #else
        #error "Not implemented for the current os"
    #endif
    exeFilePath._path = boost::filesystem::absolute(boost::filesystem::path(buffer));
    });
    return exeFilePath;
}
const Path& Path::exeDir() noexcept
{
    static Path exeDirPath;
    static std::once_flag initFlag;
    std::call_once(initFlag, []()
    {
        exeDirPath._path = exeFile()._path.parent_path();
    });
    return exeDirPath;
}
const Path& Path::tmpDir() noexcept
{
    static Path tmpDirPath;
    static std::once_flag initFlag;
    std::call_once(initFlag, []()
    {
        tmpDirPath._path = boost::filesystem::temp_directory_path();
    });
    return tmpDirPath;
}
}