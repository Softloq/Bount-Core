/**
 * @file Path.cppm
 * @author Brandon Foster (Paradox Gene)
 */

module;

#include "Bount/Filesystem/Path.hpp"
#include <boost/filesystem.hpp>

export module Bount.Filesystem.Path;

export namespace Bount::Filesystem
{
class Path
{
    boost::filesystem::path _path;

public:
    BOUNT_CORE_API ~Path() noexcept = default;

    BOUNT_CORE_API Path(const Path& path) noexcept = default;
    BOUNT_CORE_API Path& operator=(const Path& path) noexcept = default;

    BOUNT_CORE_API Path(Path&& path) noexcept = default;
    BOUNT_CORE_API Path& operator=(Path&& path) noexcept = default;

    BOUNT_CORE_API Path() noexcept = default;

    BOUNT_CORE_API Path(const String& pathString) noexcept;
    BOUNT_CORE_API Path(String&& pathString) noexcept;

    BOUNT_CORE_API [[nodiscard]] Bool exists() const noexcept;
    BOUNT_CORE_API [[nodiscard]] Bool isAbsolute() const noexcept;
    BOUNT_CORE_API [[nodiscard]] Bool isRelative() const noexcept;
    BOUNT_CORE_API [[nodiscard]] Bool isDir() const noexcept;
    BOUNT_CORE_API [[nodiscard]] Bool isFile() const noexcept;

    BOUNT_CORE_API [[nodiscard]] String filename() const noexcept;
    BOUNT_CORE_API [[nodiscard]] String ext() const noexcept;

    BOUNT_CORE_API void append(const Path& path) noexcept;
    BOUNT_CORE_API [[nodiscard]] Path operator/(const Path& path) const noexcept;

    BOUNT_CORE_API void normalize() noexcept;

    BOUNT_CORE_API [[nodiscard]] Path parent() const noexcept;
    BOUNT_CORE_API [[nodiscard]] String toString() const noexcept;
};
}
