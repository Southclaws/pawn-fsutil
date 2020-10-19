/// @brief File system namespace
namespace FileSystem
{
    /// @brief File type enumerator
    enum class EFileType
    {
        /// @brief No file type
        None,

        /// @brief File not found
        NotFound,

        /// @brief Is regular file type
        Regular,

        /// @brief Is directory file type
        Directory,

        /// @brief Is symbolic link file type
        SymbolicLink,

        /// @brief Is block file type
        Block,

        /// @brief Is character file type
        Character,

        /// @brief Is "first in, first out" file type
        FirstInFirstOut,

        /// @brief Socket file type
        Socket,

        /// @brief Unknown file type
        Unknown
    };
}
