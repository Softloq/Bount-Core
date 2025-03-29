#include "Bount/Core/Precompiled.hpp"
#include "Bount/Core/Filesystem.hpp"
#include <boost/filesystem.hpp>

#ifdef _WIN32
#include <windows.h> // Include the Windows header
#endif

namespace Bount::Core::Filesystem
{
BOUNT_CORE_API String BinPath(const String& path)
{
    try
    {
    #ifdef _WIN32
        char buffer[MAX_PATH];
        GetModuleFileNameA(NULL, buffer, MAX_PATH);
        boost::filesystem::path right_path(path);
        if (right_path.is_absolute())
        {
            return right_path.string();
        }
        else return boost::filesystem::path(buffer).parent_path().append(right_path).string();
    #else
        #error Unsupported Operating System.
    #endif
    }
    catch (const boost::filesystem::filesystem_error& ex)
    {
        std::cerr << "Error getting executable path: " << ex.what() << std::endl;
        return "";
    }
}
}