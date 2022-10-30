#pragma once
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
// anonymous namespace to prevent includes from including std into other files
namespace
{
	using namespace std::filesystem;
	using namespace std;
}

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
			string Name;
			EFileType Type = EFileType::Directory;
			string Extension;
			string FullyQualifiedPath;
			string RelativePath;
			string Drive;
			string SLastModified;
			string SLastAccessed;
			string SLastStatusChange;
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
		bool GetFileInformation(path& file, FileInformation& fileInfo);

		/// <summary>
		/// Gets the current directory for the running program.
		/// </summary>
		/// <returns>std::path of the current directory</returns>
		path CurrentDirectory();

		/// <summary>
		/// Create directory(s) if it doesn't already exist.
		/// </summary>
		/// <param name="dir">Path of Directory</param>
		/// <returns>true on creation success</returns>
		bool DirectoryCreate(const path& dir);

		/// <summary>
		/// Copies an existing directory to a destination.
		/// </summary>
		/// <param name="source">source directory to copy from</param>
		/// <param name="destination">destination directory to copy to</param>
		/// <returns>true on copy success</returns>
		bool DirectoryCopy(const path& source, const path& destination);
		
		/// <summary>
		/// Checks if a given path exists or not on this file system.
		/// </summary>
		/// <param name="file_or_dir">A path to a file or directory</param>
		/// <returns>true if the file exists</returns>
		bool PathExists(const path& file_or_dir);

		/// <summary>
		/// Delete a given path and all contained within if it is a folder
		/// </summary>
		/// <param name="to_delete">The file or folder to be deleted</param>
		/// <returns>true if the path is deleted</returns>
		bool PathDelete(const path& to_delete);
		
		/// <summary>
		/// Create a new file, if it exists overwrite by default
		/// </summary>
		/// <param name="file">path of the file to create</param>
		/// <param name="stream">an fstream allowing read/write to new file</param>
		/// <param name="bOverwrite">boolean flag to overwrite the file if it exists (default true)</param>
		/// <returns>true on file creation success</returns>
		bool FileCreate(const path& file, fstream& stream, bool bOverwrite = true);

		/// <summary>
		/// Copy a file from a source location to a destination
		/// </summary>
		/// <param name="src">source file to copy</param>
		/// <param name="dest">destination file to copy to</param>
		/// <returns>true on file copy success</returns>
		bool FileCopy(const path& src, const path& dest);

		/// <summary>
		/// Gets the size of a file in bytes.
		/// </summary>
		/// <param name="file">file to read the size of</param>
		/// <returns>uint64_t indicating the size</returns>
		uint64_t FileGetSize(const path& file);

		/// <summary>
		/// Enumerates a directory for all files and returns a vector of file paths
		/// Can be recursive if bRecursive is set to true
		/// </summary>
		/// <param name="dir">path of directory to enumerate</param>
		/// <param name="bRecursive">if true enumerates all child files and folders</param>
		/// <returns>a vector of file paths</returns>
		vector<path> FilesIn(const path& dir, bool bRecursive = false);

		/// <summary>
		/// Gets the relative path of a file
		/// </summary>
		/// <param name="file">the file path to make relative</param>
		/// <param name="bAbsolute">set to true if the file path is absolute</param>
		/// <returns>a relative path to the file</returns>
		path FilePathNormalize(path& file, bool bAbsolute = false);

		/// <summary>
		/// Appends a path to another
		/// </summary>
		/// <param name="a">base path</param>
		/// <param name="b">path to append to a</param>
		/// <returns>the appended path</returns>
		void Append(path& a, path& b);

		/// <summary>
		/// Appends a string to a path
		/// </summary>
		/// <param name="a">base path</param>
		/// <param name="b">path to append to a</param>
		/// <returns>the appended path</returns>
		void Append(path& a, string& b);
		
		/// <summary>
		/// Gets the current directory and appends a relative path to it
		/// </summary>
		/// <param name="a">a relative path</param>
		/// <returns></returns>
		path FromCurrentDirectory(path& a);

		/// <summary>
		/// Gets the current directory and appends the string to it
		/// </summary>
		/// <param name="a">a relative path</param>
		/// <returns></returns>
		path FromCurrentDirectory(string& a);

#define GetAsset(AssetType, AssetName) GetAssetLocation(#AssetType, AssetName);

		path GetAssetLocation(string& AssetType, string& AssetName);

		//------------------------------------------------------------------------
		//						 std::string overloads 
		//------------------------------------------------------------------------

		/// <summary>
		/// gets the current directory for the running program.
		/// </summary>
		/// <returns>std::string of the current directory</returns>
		string CurrentDirectoryToString();

		/// <summary>
		/// Create a directory if it doesn't already exist.
		/// </summary>
		/// <param name="dir">Path of Directory</param>
		/// <returns>true on creation success</returns>
		bool DirectoryCreate(const string& dir);

		/// <summary>
		/// copies an existing directory to a destination.
		/// </summary>
		/// <param name="source">source directory to copy from</param>
		/// <param name="destination">destination directory to copy to</param>
		/// <returns>true on copy success</returns>
		bool DirectoryCopy(const string& source, const string& destination);
		
		/// <summary>
		/// Checks if a given path exists or not on this file system.
		/// </summary>
		/// <param name="file_or_dir">a path to a file or directory</param>
		/// <returns>true if the file exists</returns>
		bool PathExists(const string& file_or_dir);

		/// <summary>
		/// Delete a given path and all contained within if it is a folder
		/// </summary>
		/// <param name="to_delete">the file or folder to be deleted</param>
		/// <returns>true if the path is deleted</returns>
		bool PathDelete(const string& to_delete);
		
		/// <summary>
		/// Create a new file, if it exists overwrite by default
		/// </summary>
		/// <param name="file">path of the file to create</param>
		/// <param name="stream">an fstream allowing read/write to new file</param>
		/// <param name="bOverwrite">boolean flag to overwrite the file if it exists (default true)</param>
		/// <returns>true on file creation success</returns>
		bool FileCreate(const string& file, fstream& stream, bool bOverwrite = true);

		/// <summary>
		/// Copy a file from a source location to a destination
		/// </summary>
		/// <param name="src">source file to copy</param>
		/// <param name="dest">destination file to copy to</param>
		/// <returns>true on file copy success</returns>
		bool FileCopy(const string& src, const string& dest);

		/// <summary>
		/// Gets the size of a file in bytes.
		/// </summary>
		/// <param name="file">file to read the size of</param>
		/// <returns>uint64_t indicating the size</returns>
		uint64_t FileGetSize(const string& file);

		/// <summary>
		/// Enumerates a directory for all files and returns a vector of file paths
		/// Can be recursive if bRecursive is set to true
		/// </summary>
		/// <param name="dir">path of directory to enumerate</param>
		/// <param name="bRecursive">if true enumerates all child files and folders</param>
		/// <returns>a vector of file paths as strings</returns>
		vector<string> FilesIn(const string& dir, bool bRecursive = false);

		/// <summary>
		/// Gets the relative path of a file
		/// </summary>
		/// <param name="file">the file path to make relative</param>
		/// <param name="bAbsolute">set to true if the file path is absolute</param>
		/// <returns>a relative path to the file as a string</returns>
		string FilePathNormalize(string& file, bool bAbsolute = false);

	namespace internal
	{
		void ProcessError(const string& function_name,filesystem_error& exception);
		void TestAll();
	}
}
}