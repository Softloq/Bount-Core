module;

#include "Bount/Filesystem/File.hpp"
#include <boost/filesystem.hpp>
#include <cstddef> // for at least SIZE_MAX.
#include <fstream>

export module Bount.Filesystem.File;
export import Bount.Filesystem.Path;

export namespace Bount::Filesystem
{
// Classes

class FileBuffer;
class File;

/**
 * Auxiliary Class for a File.
 * Character buffer for file reading or writing.
 */
class FileBuffer
{
public:
    // Constructors/Destructor functions

    BOUNT_CORE_API ~FileBuffer() noexcept = default;

    BOUNT_CORE_API FileBuffer(const FileBuffer& buffer) noexcept = default;
    BOUNT_CORE_API FileBuffer& operator=(const FileBuffer& buffer) noexcept = default;

    BOUNT_CORE_API FileBuffer(FileBuffer&& buffer) noexcept = default;
    BOUNT_CORE_API FileBuffer& operator=(FileBuffer&& buffer) noexcept = default;

    BOUNT_CORE_API FileBuffer() noexcept = default;
};

/**
 * Fundamental class for the filesystem.
 * Represents a file that may or may not exist on the system.
 */
class File
{
public:
    enum class Modes : Signed
    {
        None = 0 << 0,
        Read = 1 << 1,
        Write = 1 << 2,
        Append = 1 << 3,
        Binary = 1 << 4,
        Text = 1 << 5
    };

    [[nodiscard]] inline friend constexpr Modes operator|(Modes lhs, Modes rhs) noexcept { return static_cast<Modes>(static_cast<Signed>(lhs) | static_cast<Signed>(rhs)); }
    [[nodiscard]] inline friend constexpr Modes operator&(Modes lhs, Modes rhs) noexcept { return static_cast<Modes>(static_cast<Signed>(lhs) & static_cast<Signed>(rhs)); }
    [[nodiscard]] inline friend constexpr Modes operator~(Modes mode) noexcept { return static_cast<Modes>(~static_cast<Signed>(mode)); }
    
public:
    // Constructors/Destructor functions

    BOUNT_CORE_API ~File() noexcept = default;

    BOUNT_CORE_API File(const File& file) noexcept = default;
    BOUNT_CORE_API File& operator=(const File& file) noexcept = default;

    BOUNT_CORE_API File(File&& file) noexcept = default;
    BOUNT_CORE_API File& operator=(File&& file) noexcept = default;

    BOUNT_CORE_API File() noexcept = default;

    BOUNT_CORE_API File(const Path& path, Modes modes = Modes::Text | Modes::Append) noexcept;
    BOUNT_CORE_API File(Path&& path, Modes modes = Modes::Text | Modes::Append) noexcept;

    // Member functions

    BOUNT_CORE_API void open(const Path& path, Modes modes = Modes::Text | Modes::Append) noexcept;
    BOUNT_CORE_API void open(Modes modes = Modes::Text | Modes::Append) noexcept;
    BOUNT_CORE_API void close() noexcept;

    BOUNT_CORE_API void write(const FileBuffer& buffer) noexcept;
    BOUNT_CORE_API void write(const String& content) noexcept;

    BOUNT_CORE_API [[nodiscard]] FileBuffer readBuf(SizeT byteCount = SIZE_MAX) const noexcept;
    BOUNT_CORE_API [[nodiscard]] String readChars(SizeT charCount = SIZE_MAX) const noexcept;
    BOUNT_CORE_API [[nodiscard]] String readLines(SizeT lineCount = 1) const noexcept;

    BOUNT_CORE_API [[nodiscard]] SizeT size() const noexcept;
    BOUNT_CORE_API [[nodiscard]] Bool exists() const noexcept;
    
    // Non-member functions

    BOUNT_CORE_API friend std::ostream& operator<<(std::ostream& os, const File& file);
    BOUNT_CORE_API friend std::istream& operator>>(std::istream& is, File& file);

private:
    std::shared_ptr<std::fstream> _file;
    Path _path;
};
}
