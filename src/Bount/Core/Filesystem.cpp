#include "Bount/Core/Precompiled.hpp"
#include "Bount/Core/Filesystem.hpp"
#include <boost/filesystem.hpp>

#if defined(BOUNT_WINDOWS)
#include <windows.h>
#endif

namespace Bount::Filesystem
{
BOUNT_CORE_API Path::Path(Base base, const String& relPath) noexcept
{
    setPath(base, relPath);
}
BOUNT_CORE_API void Path::setPath(Base base, const String& relPath) noexcept
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
BOUNT_CORE_API String Path::toString() const noexcept
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
BOUNT_CORE_API Path::operator String() const noexcept
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
BOUNT_CORE_API const String& Path::BaseString(Base base) noexcept
{
    try
    {
    #if defined(BOUNT_WINDOWS)
        static char binBuffer[MAX_PATH];
        GetModuleFileNameA(NULL, binBuffer, MAX_PATH);

        // uses the bin path to define the other paths

        static boost::filesystem::path binPath = boost::filesystem::absolute(boost::filesystem::path(binBuffer));
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
    #else
        #error "Not supported yet"
    #endif
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