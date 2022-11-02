#pragma once
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
// anonymous namespace to prevent includes from including std into other files
namespace ME
{
	namespace Disk
	{
		/// <summary>
		/// Describes a files security permissions (owner)
		/// </summary>
		struct SecurityPermissions
		{
			bool bReadable :1 = false;
			bool bWritable :1 = false;
			bool bExecutable :1 = false;
			bool bUnused :5 = false;
		};

		/// <summary>
		/// Describes the type of file, regular being the normal file type.
		/// </summary>
		enum class EFileType
		{
			CharacterSpecialFile,
			Directory,
			Pipe,
			Regular,
		};

		/// <summary>
		/// A structure detailing information about a file
		/// </summary>
		struct FileInformation
		{
			std::string Name;
			EFileType Type = EFileType::Directory;
			std::string Extension;
			std::string FullyQualifiedPath;
			std::string RelativePath;
			std::string Drive;
			std::string SLastModified;
			std::string SLastAccessed;
			std::string SLastStatusChange;
			time_t LastModified = 0;
			time_t LastAccessed = 0;
			time_t LastStatusChange = 0;
			SecurityPermissions Permissions;
			uint64_t SizeInBytes = 0;
		};

		/// <summary>
		/// Gathers as much info about a file as possible
		/// </summary>
		/// <param name="file">the target file to investigate</param>
		/// <param name="fileInfo">the FileInformation structure</param>
		/// <returns></returns>
		bool GetFileInformation(std::filesystem::path& file, FileInformation& fileInfo);

		/// <summary>
		/// Gets the current directory for the running program.
		/// </summary>
		/// <returns>std::path of the current directory</returns>
		std::filesystem::path CurrentDirectory();

		/// <summary>
		/// Create directory(s) if it doesn't already exist.
		/// </summary>
		/// <param name="dir">Path of Directory</param>
		/// <returns>true on creation success</returns>
		bool DirectoryCreate(const std::filesystem::path& dir);

		/// <summary>
		/// Copies an existing directory to a destination.
		/// </summary>
		/// <param name="source">source directory to copy from</param>
		/// <param name="destination">destination directory to copy to</param>
		/// <returns>true on copy success</returns>
		bool DirectoryCopy(const std::filesystem::path& source, const std::filesystem::path& destination);
		
		/// <summary>
		/// Checks if a given path exists or not on this file system.
		/// </summary>
		/// <param name="file_or_dir">A path to a file or directory</param>
		/// <returns>true if the file exists</returns>
		bool PathExists(const std::filesystem::path& file_or_dir);

		/// <summary>
		/// Delete a given path and all contained within if it is a folder
		/// </summary>
		/// <param name="to_delete">The file or folder to be deleted</param>
		/// <returns>true if the path is deleted</returns>
		bool PathDelete(const std::filesystem::path& to_delete);
		
		/// <summary>
		/// Create a new file, if it exists overwrite by default
		/// </summary>
		/// <param name="file">path of the file to create</param>
		/// <param name="stream">an fstream allowing read/write to new file</param>
		/// <param name="bOverwrite">boolean flag to overwrite the file if it exists (default true)</param>
		/// <returns>true on file creation success</returns>
		bool FileCreate(const std::filesystem::path& file, std::fstream& stream, bool bOverwrite = true);

		/// <summary>
		/// Copy a file from a source location to a destination
		/// </summary>
		/// <param name="src">source file to copy</param>
		/// <param name="dest">destination file to copy to</param>
		/// <returns>true on file copy success</returns>
		bool FileCopy(const std::filesystem::path& src, const std::filesystem::path& dest);

		/// <summary>
		/// Gets the size of a file in bytes.
		/// </summary>
		/// <param name="file">file to read the size of</param>
		/// <returns>uint64_t indicating the size</returns>
		uint64_t FileGetSize(const std::filesystem::path& file);

		/// <summary>
		/// Enumerates a directory for all files and returns a vector of file paths
		/// Can be recursive if bRecursive is set to true
		/// </summary>
		/// <param name="dir">path of directory to enumerate</param>
		/// <param name="bRecursive">if true enumerates all child files and folders</param>
		/// <returns>a vector of file paths</returns>
		std::vector<std::filesystem::path> FilesIn(const std::filesystem::path & dir, bool bRecursive = false);

		/// <summary>
		/// Gets the relative path of a file
		/// </summary>
		/// <param name="file">the file path to make relative</param>
		/// <param name="bAbsolute">set to true if the file path is absolute</param>
		/// <returns>a relative path to the file</returns>
		std::filesystem::path FilePathNormalize(std::filesystem::path& file, bool bAbsolute = false);

		/// <summary>
		/// Appends a path to another
		/// </summary>
		/// <param name="a">base path</param>
		/// <param name="b">path to append to a</param>
		/// <returns>the appended path</returns>
		void Append(std::filesystem::path& a, std::filesystem::path& b);

		/// <summary>
		/// Appends a std::string to a path
		/// </summary>
		/// <param name="a">base path</param>
		/// <param name="b">path to append to a</param>
		/// <returns>the appended path</returns>
		void Append(std::filesystem::path& a, std::string& b);
		
		/// <summary>
		/// Gets the current directory and appends a relative path to it
		/// </summary>
		/// <param name="a">a relative path</param>
		/// <returns></returns>
		std::filesystem::path FromCurrentDirectory(std::filesystem::path& a);

		/// <summary>
		/// Gets the current directory and appends the std::string to it
		/// </summary>
		/// <param name="a">a relative path</param>
		/// <returns></returns>
		std::filesystem::path FromCurrentDirectory(std::string& a);

#define GetAsset(AssetType, AssetName) GetAssetLocation(#AssetType, AssetName);

		std::filesystem::path GetAssetLocation(std::string& AssetType, std::string& AssetName);

		//------------------------------------------------------------------------
		//						 std::std::string overloads 
		//------------------------------------------------------------------------

		/// <summary>
		/// gets the current directory for the running program.
		/// </summary>
		/// <returns>std::std::string of the current directory</returns>
		std::string CurrentDirectoryToString();

		/// <summary>
		/// Create a directory if it doesn't already exist.
		/// </summary>
		/// <param name="dir">Path of Directory</param>
		/// <returns>true on creation success</returns>
		bool DirectoryCreate(const std::string& dir);

		/// <summary>
		/// copies an existing directory to a destination.
		/// </summary>
		/// <param name="source">source directory to copy from</param>
		/// <param name="destination">destination directory to copy to</param>
		/// <returns>true on copy success</returns>
		bool DirectoryCopy(const std::string& source, const std::string& destination);
		
		/// <summary>
		/// Checks if a given path exists or not on this file system.
		/// </summary>
		/// <param name="file_or_dir">a path to a file or directory</param>
		/// <returns>true if the file exists</returns>
		bool PathExists(const std::string& file_or_dir);

		/// <summary>
		/// Delete a given path and all contained within if it is a folder
		/// </summary>
		/// <param name="to_delete">the file or folder to be deleted</param>
		/// <returns>true if the path is deleted</returns>
		bool PathDelete(const std::string& to_delete);
		
		/// <summary>
		/// Create a new file, if it exists overwrite by default
		/// </summary>
		/// <param name="file">path of the file to create</param>
		/// <param name="stream">an fstream allowing read/write to new file</param>
		/// <param name="bOverwrite">boolean flag to overwrite the file if it exists (default true)</param>
		/// <returns>true on file creation success</returns>
		bool FileCreate(const std::string& file, std::fstream& stream, bool bOverwrite = true);

		/// <summary>
		/// Copy a file from a source location to a destination
		/// </summary>
		/// <param name="src">source file to copy</param>
		/// <param name="dest">destination file to copy to</param>
		/// <returns>true on file copy success</returns>
		bool FileCopy(const std::string& src, const std::string& dest);

		/// <summary>
		/// Gets the size of a file in bytes.
		/// </summary>
		/// <param name="file">file to read the size of</param>
		/// <returns>uint64_t indicating the size</returns>
		uint64_t FileGetSize(const std::string& file);

		/// <summary>
		/// Enumerates a directory for all files and returns a vector of file paths
		/// Can be recursive if bRecursive is set to true
		/// </summary>
		/// <param name="dir">path of directory to enumerate</param>
		/// <param name="bRecursive">if true enumerates all child files and folders</param>
		/// <returns>a vector of file paths as std::strings</returns>
		std::vector<std::string> FilesIn(const std::string & dir, bool bRecursive = false);

		/// <summary>
		/// Gets the relative path of a file
		/// </summary>
		/// <param name="file">the file path to make relative</param>
		/// <param name="bAbsolute">set to true if the file path is absolute</param>
		/// <returns>a relative path to the file as a std::string</returns>
		std::string FilePathNormalize(std::string& file, bool bAbsolute = false);

	namespace internal
	{
		void ProcessError(const std::string& function_name, std::filesystem::filesystem_error & exception);
		void TestAll();
	}
}
}