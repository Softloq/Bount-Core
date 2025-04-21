/**
 * @file Filesystem.hpp
 * @brief Standard Filesystem sublibrary.
 * @author Brandon Foster (Paradox Gene)
 */

#ifndef BOUNT_CORE_FILESYSTEM_HPP
#define BOUNT_CORE_FILESYSTEM_HPP

#include "Bount/Core/Datatypes.hpp"
#include <boost/filesystem.hpp>

namespace Bount::Filesystem
{
/** @brief Standard Filesystem Path class manages path strings. */
class Path
{
    boost::filesystem::path _path;

public:
    
    /** @brief Standard Filesystem Base enums are common base paths. */
    enum class Base
    {
        /** Top-level folder of the app. */
        App,
        /** Folder containing the app executable. */
        Bin,
        /** Folder containing the app resources. */
        Resources
    };
    
    /**
     * @param base Begins the path.
     * @param relPath Appends to the base path.
     * 
     * @brief Creates a Path instance of "{base}/{relPath}".
     */
    BOUNT_CORE_API Path(Base base, const String& relPath) noexcept;

    /**
     * @param base Begins the path.
     * @param relPath Appends to the base path.
     * 
     * @brief Updates the path string to "{base}/{relPath}".
     */
    BOUNT_CORE_API void setPath(Base base, const String& relPath) noexcept;
    
    /** @return Returns a newly created Bount String from the path. */
    BOUNT_CORE_API String toString() const noexcept;

    /** @return Converts the path to a newly created Bount String. */
    BOUNT_CORE_API operator String() const noexcept;

    BOUNT_CORE_API static const String& BaseString(Base base) noexcept;
};
}

#endif