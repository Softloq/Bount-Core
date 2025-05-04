module;

#include "Bount/Filesystem/Path.hpp"
#include <boost/filesystem.hpp>

export module Bount.Filesystem.Path;

export namespace Bount::Filesystem
{
// Classes

class Path;

/**
 * Fundamental class for the filesystem.
 * Can represent a file or directory path.
 * Useful for custom path manipulation.
 */
class Path
{
public:
    // Constructors/Destructor functions

    BOUNT_CORE_API ~Path() noexcept = default;

    BOUNT_CORE_API Path(const Path& path) noexcept = default;
    BOUNT_CORE_API Path& operator=(const Path& path) noexcept = default;

    BOUNT_CORE_API Path(Path&& path) noexcept = default;
    BOUNT_CORE_API Path& operator=(Path&& path) noexcept = default;

    BOUNT_CORE_API Path() noexcept = default;

    BOUNT_CORE_API Path(const String& path) noexcept;
    BOUNT_CORE_API Path(String&& path) noexcept;

    // Member functions

    BOUNT_CORE_API void append(const Path& path) noexcept;
    BOUNT_CORE_API [[nodiscard]] Path& operator/=(const Path& path) noexcept;

    BOUNT_CORE_API void concat(const Path& path) noexcept;
    BOUNT_CORE_API [[nodiscard]] Path& operator+=(const Path& path) noexcept;
    
    BOUNT_CORE_API [[nodiscard]] Bool isAbsolute() const noexcept;
    BOUNT_CORE_API [[nodiscard]] Bool isRelative() const noexcept;
    BOUNT_CORE_API [[nodiscard]] Bool isFile() const noexcept;
    BOUNT_CORE_API [[nodiscard]] Bool isDir() const noexcept;
    BOUNT_CORE_API [[nodiscard]] Bool exists() const noexcept;

    BOUNT_CORE_API [[nodiscard]] Path absolute() const noexcept;
    BOUNT_CORE_API [[nodiscard]] Path relative(const Path& path = exeDir()) const noexcept;
    BOUNT_CORE_API [[nodiscard]] Path canonical() const noexcept;
    BOUNT_CORE_API [[nodiscard]] Path normalize() const noexcept;

    BOUNT_CORE_API [[nodiscard]] Bool hasFilename() const noexcept;
    BOUNT_CORE_API [[nodiscard]] Bool hasExtension() const noexcept;
    BOUNT_CORE_API [[nodiscard]] Bool hasStem() const noexcept;
    BOUNT_CORE_API [[nodiscard]] Bool hasParent() const noexcept;

    BOUNT_CORE_API [[nodiscard]] Path filename() const noexcept;
    BOUNT_CORE_API [[nodiscard]] Path extension() const noexcept;
    BOUNT_CORE_API [[nodiscard]] Path stem() const noexcept;
    BOUNT_CORE_API [[nodiscard]] Path parent() const noexcept;

    BOUNT_CORE_API [[nodiscard]] String toString() const noexcept;

    // Non-member functions

    BOUNT_CORE_API [[nodiscard]] friend Path operator/(const Path& lhs, const Path& rhs) noexcept;
    BOUNT_CORE_API [[nodiscard]] friend Path operator+(const Path& lhs, const Path& rhs) noexcept;

    BOUNT_CORE_API [[nodiscard]] static const Path& exeFile() noexcept;
    BOUNT_CORE_API [[nodiscard]] static const Path& exeDir() noexcept;
    BOUNT_CORE_API [[nodiscard]] static const Path& tmpDir() noexcept;

private:
    boost::filesystem::path _path;
};
}
