#include "Bount/Core/Precompiled.hpp"
#include <boost/filesystem.hpp>

import Bount.Filesystem;

#if defined(BOUNT_WINDOWS)
    #include <windows.h> // For GetModuleFileNameA
#elif defined(BOUNT_LINUX)
    #include <limits.h> // For PATH_MAX
    #include <unistd.h> // For readlink
#endif

namespace Bount::Filesystem
{
Path::Path(Base base, const String& relPath) noexcept
{
    setPath(base, relPath);
}
void Path::setPath(Base base, const String& relPath) noexcept
{
    try
    {
        _path = boost::filesystem::path(BaseString(base)).append(relPath);
    }
    catch (const boost::filesystem::filesystem_error& e)
    {
    #if defined(BOUNT_DEBUG)
        std::cerr << "Error getting path: " << e.what() << std::endl;
    #endif
    }
}
String Path::toString() const noexcept
{
    try
    {
        return _path.string();
    }
    catch (const boost::filesystem::filesystem_error& e)
    {
    #if defined(BOUNT_DEBUG)
        std::cerr << "Error getting path: " << e.what() << std::endl;
    #endif
    }
    return "";
}
Path::operator String() const noexcept
{
    try
    {
        return _path.string();
    }
    catch (const boost::filesystem::filesystem_error& e)
    {
    #if defined(BOUNT_DEBUG)
        std::cerr << "Error getting path: " << e.what() << std::endl;
    #endif
    }
    return "";
}
const String& Path::BaseString(Base base) noexcept
{
    try
    {
        // create the bin buffer (OS-Specific)
    #if defined(BOUNT_WINDOWS)
        static char binBuffer[MAX_PATH];
        GetModuleFileNameA(NULL, binBuffer, MAX_PATH);
    #elif defined(BOUNT_LINUX)
        static char binBuffer[PATH_MAX];
        static ssize_t count = readlink("/proc/self/exe", binBuffer, PATH_MAX);
    #else
        #error "Not supported yet"
    #endif

        // uses the bin path to define the other paths

        static boost::filesystem::path binPath = boost::filesystem::absolute(boost::filesystem::path(binBuffer)).parent_path();
        static String binPathString = binPath.string();
        
        switch(base)
        {
        case Base::App: {
            static boost::filesystem::path appPath = boost::filesystem::absolute(binPath.append("../"));
            static String appPathString = appPath.string();
            return appPathString;
        }
        case Base::Bin: {
            return binPathString;
        }
        case Base::Resources: {
            static boost::filesystem::path resPath = boost::filesystem::absolute(binPath.append("../Resources"));
            static String resPathString = resPath.string();
            return resPathString;
        }
        }
    }
    catch (const boost::filesystem::filesystem_error& e)
    {
    #if defined(BOUNT_DEBUG)
        std::cerr << "Error getting path: " << e.what() << std::endl;
    #endif
    }
    return "";
}
}