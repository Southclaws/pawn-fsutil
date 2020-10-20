#pragma once

#include <amx/amx.h>

/// @brief File system namespace
namespace FileSystem
{
	/// @brief File system natives namespace
	namespace Natives
	{
		/// @brief Invalid directory enumerator ID
		static const cell INVALID_DIRECTORY_ENUMERATOR_ID(-1);

		/// @brief Does file system object exist
		/// @param amx AMX
		/// @param params Function parameters
		/// @return "1" if file exists, otherwise "0"
		cell DoesExist(AMX* amx, cell* params);

		/// @brief Create directory
		/// @param amx AMX
		/// @param params Function parameters
		/// @return "1" if directory was successfully created, otherwise "0"
		cell CreateDirectory(AMX* amx, cell* params);

		/// @brief Remove directory
		/// @param amx AMX
		/// @param params Function parameters
		/// @return "1" if directory was successfully removed, otherwise "0"
		cell RemoveDirectory(AMX* amx, cell* params);

		/// @brief Create directory enumerator
		/// @param amx AMX
		/// @param params Function parameters
		/// @return Directory enumerator ID if successful, otherwise "FileSystem::Natives::INVALID_DIRECTORY_ENUMERATOR_ID"
		cell CreateDirectoryEnumerator(AMX* amx, cell* params);

		/// @brief Enumerate directory
		/// @param amx AMX
		/// @param params Function parameters
		/// @return "1" if enumeration was successful, otherwise "0"
		cell EnumerateDirectory(AMX* amx, cell* params);

		/// @brief Destroy directory enumerator
		/// @param amx AMX
		/// @param params Function parameters
		/// @return "1" if directory enumerator was successfully destroyed, otherwise "0"
		cell DestroyDirectoryEnumerator(AMX* amx, cell* params);

		/// @brief Move file
		/// @param amx AMX
		/// @param params Function parameters
		/// @return "1" if file was moved successfully, otherwise "0"
		cell MoveFile(AMX* amx, cell* params);

		/// @brief Copy file
		/// @param amx AMX
		/// @param params Function parameters
		/// @return "1" if file was copied successfully, otherwise "0"
		cell CopyFile(AMX* amx, cell* params);

		/// @brief Get path separator
		/// @param amx AMX
		/// @param params Function parameters
		/// @return Path seperator
		cell GetPathSeparator(AMX* amx, cell* params);

		/// @brief Combine paths
		/// @param amx AMX
		/// @param params Function parameters
		/// @return Nothing
		cell CombinePaths(AMX* amx, cell* params);

		/// @brief Get file name
		/// @param amx AMX
		/// @param params Function parameters
		/// @return Nothing
		cell GetFileName(AMX* amx, cell* params);

		/// @brief Get directory path
		/// @param amx AMX
		/// @param params Function parameters
		/// @return Nothing
		cell GetDirectoryPath(AMX* amx, cell* params);

		/// @brief Get file extension
		/// @param amx AMX
		/// @param params Function parameters
		/// @return Nothing
		cell GetFileExtension(AMX* amx, cell* params);
	};
};
