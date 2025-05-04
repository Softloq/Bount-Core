module;

#include "Bount/Filesystem/Dir.hpp"
#include <boost/filesystem.hpp>

export module Bount.Filesystem.Dir;
export import Bount.Filesystem.File;
export import Bount.Filesystem.Path;

export namespace Bount::Filesystem
{
// Classes

class Dir;

/**
 * Fundamental class for the filesystem.
 * Represents a directory that may or may not exist on the system.
 */
class Dir
{
public:
    // Constructors/Destructor functions

    BOUNT_CORE_API ~Dir() noexcept = default;

    BOUNT_CORE_API Dir(const Dir& dir) noexcept = default;
    BOUNT_CORE_API Dir& operator=(const Dir& dir) noexcept = default;

    BOUNT_CORE_API Dir(Dir&& dir) noexcept = default;
    BOUNT_CORE_API Dir& operator=(Dir&& dir) noexcept = default;

    BOUNT_CORE_API Dir() noexcept = default;

    BOUNT_CORE_API Dir(const Path& path) noexcept;
    BOUNT_CORE_API Dir(Path&& path) noexcept;

    // Member functions
    
    BOUNT_CORE_API void create() noexcept;
    BOUNT_CORE_API void remove() noexcept;
    BOUNT_CORE_API void change(const Path& path) noexcept;
    
    BOUNT_CORE_API [[nodiscard]] Bool exists() const noexcept;
    BOUNT_CORE_API [[nodiscard]] std::vector<File> files() const noexcept;
    BOUNT_CORE_API [[nodiscard]] std::vector<Dir>  subDirs() const noexcept;

private:
    Path _path;
};
}
