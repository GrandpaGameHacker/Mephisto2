#include <spdlog/spdlog.h>
#include <Core/MephistoAssert.h>
#include <FileSystem/FileSystem.h>

using namespace std::filesystem;
using namespace std;

bool ME::Disk::GetFileInformation(path& file, FileInformation& fileInfo)
{
	if (PathExists(file) && file.has_filename())
	{
		string filePath = file.string();
		struct _stat buffer;
		int result = 0;
		char timebuf[26];
		const char *filename = filePath.c_str();
		errno_t error = 0;
		result = _stat(filename, &buffer);
		if (result != 0)
		{
			spdlog::error("ME::Disk::{} problem getting _stat structure info!\nError Report:", __func__);
			switch (error)
			{
			case ENOENT:
				spdlog::error("_stat: File not found");
				break;
			case EINVAL:
				spdlog::error("_stat: Invalid parameter");
				break;
			case EACCES:
				spdlog::error("_stat: Permission denied");
				break;
			case EIO:
				spdlog::error("_stat: FileSystem Error");
				break;
			case ENAMETOOLONG:
				spdlog::error("_stat: Name too long (Exceeds PATH_MAX)");
				break;
			case ENOTDIR:
				spdlog::error("_stat: A portion on the path was not a directory");
				break;
			default:
				spdlog::error("_stat: Unknown/Unhandled error");
				break;
			}
		}
		else
		{
			fileInfo.Name = file.filename().string();
			fileInfo.Extension = file.extension().string();
			fileInfo.FullyQualifiedPath = filePath;
			fileInfo.RelativePath = FilePathNormalize(file).string();
			char drive = 'A' + buffer.st_dev;
			fileInfo.Drive = drive;
			fileInfo.Drive.append(":");
			fileInfo.LastModified = buffer.st_mtime;
			fileInfo.LastAccessed = buffer.st_atime;
			fileInfo.LastStatusChange = buffer.st_ctime;
			fileInfo.SizeInBytes = buffer.st_size;
			error = ctime_s(timebuf, 26, &buffer.st_mtime);
			if (error)
			{
				spdlog::error("Invalid arguments to ctime_s.");
				return false;
			}

			fileInfo.SLastModified = timebuf;

			error = ctime_s(timebuf, 26, &buffer.st_atime);
			if (error)
			{
				spdlog::error("Invalid arguments to ctime_s.");
				return false;
			}

			fileInfo.SLastAccessed = timebuf;

			error = ctime_s(timebuf, 26, &buffer.st_ctime);
			if (error)
			{
				spdlog::error("Invalid arguments to ctime_s.");
				return false;
			}

			fileInfo.SLastStatusChange = timebuf;

			fileInfo.Permissions.bWritable = _S_IWRITE & buffer.st_mode;
			fileInfo.Permissions.bExecutable = _S_IEXEC & buffer.st_mode;
			fileInfo.Permissions.bReadable = _S_IREAD & buffer.st_mode;

			if (_S_IFDIR & buffer.st_mode)
			{
				fileInfo.Type = EFileType::Directory;
			}
			else if (_S_IFCHR & buffer.st_mode)
			{
				fileInfo.Type = EFileType::CharacterSpecialFile;
			}
			else if (_S_IFIFO & buffer.st_mode)
			{
				fileInfo.Type = EFileType::Pipe;
			}
			else if (_S_IFREG & buffer.st_mode)
			{
				fileInfo.Type = EFileType::Regular;
			}
			return true;
		}
	}
	return false;
}

path ME::Disk::CurrentDirectory()
{
	return current_path();
}

bool ME::Disk::DirectoryCreate(const path& dir)
{
	if (PathExists(dir))
	{
		return true;
	}
	create_directories(dir);
	if (PathExists(dir))
	{
		return true;
	}
	return false;
}

bool ME::Disk::DirectoryCopy(const path& source, const path& destination)
{
	if (PathExists(source))
	{
		try
		{
			copy(source, destination);
		}
		catch (filesystem_error e)
		{
			internal::ProcessError(__func__, e);
			return false;
		}
		if (PathExists(destination))
		{
			return true;
		}
	}
	return false;
}

bool ME::Disk::PathExists(const path& file_or_dir)
{
	return exists(file_or_dir);
}

bool ME::Disk::PathDelete(const path& to_delete)
{
	uintmax_t removed = 0;
	if (PathExists(to_delete))
	{
		try
		{
			removed = remove_all(to_delete);
		}
		catch (filesystem_error exception)
		{
			internal::ProcessError(__func__, exception);
			return false;
		}
	}
	return bool(removed);
}

bool ME::Disk::FileCreate(const path& file, fstream& stream, bool bOverwrite)
{
	if (!bOverwrite && PathExists(file))
	{
		return false;
	}
	try
	{
		auto parent = file.parent_path();
		create_directories(parent);
		stream.open(file.string(), fstream::out | fstream::in | fstream::trunc);
	}
	catch (filesystem_error exception)
	{
		internal::ProcessError(__func__, exception);
		return false;
	};

	return true;
}

bool ME::Disk::FileCopy(const path& source, const path& destination)
{
	bool success = false;
	if (PathExists(source))
	{
		try
		{
			success = copy_file(source, destination);
		}
		catch (filesystem_error exception)
		{
			internal::ProcessError(__func__, exception);
			return false;
		}
	}
	return success;
}

uint64_t ME::Disk::FileGetSize(const path& file)
{
	uint64_t size = NULL;
	if (!PathExists(file) || !file.has_filename()) return size;
	try
	{
		size = file_size(file);
	}
	catch (filesystem_error exception)
	{
		internal::ProcessError(__func__, exception);
	}
	return size;
}

vector<path> ME::Disk::FilesIn(const path& dir, bool bRecursive)
{
	vector<path> found;

	if (!PathExists(dir)) return found;

	if (!bRecursive)
	{
		for (const auto& item : directory_iterator(dir))
		{
			found.push_back(item);
		}
	}
	else
	{
		for (const auto& item : recursive_directory_iterator(dir))
		{
			found.push_back(item);
		}
	}
	return found;
}

path ME::Disk::FilePathNormalize(path& file, bool bAbsolute)
{
	path RelPath;
	try
	{
		RelPath = relative(file, current_path());
		if (bAbsolute)
		{
			return CurrentDirectory().string() + ("\\" + RelPath.string());
		}
	}
	catch (filesystem_error exception)
	{
		internal::ProcessError(__func__, exception);
	}
	return RelPath;
}

void ME::Disk::Append(path& a, path& b)
{
	a = path(a.string() + b.string());
}

void ME::Disk::Append(path& a, string& b)
{
	a = path(a.string() + b);
}

path ME::Disk::FromCurrentDirectory(path& a)
{
	path p = CurrentDirectory();
	Append(p, a);
	return p;
}

path ME::Disk::FromCurrentDirectory(string& a)
{
	path p = CurrentDirectory();
	Append(p, a);
	return p;
}

string ME::Disk::CurrentDirectoryToString()
{
	return current_path().string();
}

bool ME::Disk::DirectoryCreate(const string& dir)
{
	return DirectoryCreate(path(dir));
}


bool ME::Disk::DirectoryCopy(const string& source, const string& destination)
{
	return DirectoryCopy(path(source), path(destination));
}

bool ME::Disk::PathExists(const string& file_or_dir)
{
	return PathExists(path(file_or_dir));
}

bool ME::Disk::PathDelete(const string& to_delete)
{
	return PathDelete(path(to_delete));
}

bool ME::Disk::FileCreate(const string& file, fstream& stream, bool bOverwrite)
{
	return FileCreate(path(file), stream, bOverwrite);
}

bool ME::Disk::FileCopy(const string& src, const string& dest)
{
	return FileCopy(path(src), path(dest));
}

uint64_t ME::Disk::FileGetSize(const string& file)
{
	return FileGetSize(path(file));
}

vector<string> ME::Disk::FilesIn(const string& dir, bool bRecursive)
{
	vector<string> found;
	if (!bRecursive)
	{
		for (const auto& item : directory_iterator(dir))
		{
			string item_path = path(item).string();
			found.push_back(item_path);
		}
	}
	else
	{
		for (const auto& item : recursive_directory_iterator(dir))
		{
			string item_path = path(item).string();
			found.push_back(item_path);
		}
	}
	return found;
}

string ME::Disk::FilePathNormalize(string& file, bool bAbsolute)
{
	auto PathFile = path(file);
	auto PathResult = FilePathNormalize(PathFile, bAbsolute);
	return PathResult.string();
}

void ME::Disk::internal::ProcessError(const string& function_name, filesystem_error& exception)
{
	auto code = exception.code();
	spdlog::error("ME::Disk::{} Exception: {} : {}", function_name, exception.what(), code.message());
}

void ME::Disk::internal::TestAll()
{
	spdlog::debug("Running All ME::Disk Tests... (Filesystem.cpp)");

	spdlog::debug("Testing getting current directory...");
	path CurrDir1 = CurrentDirectory();
	string CurrDir2 = CurrentDirectoryToString();
	MEPH_ASSERT(CurrDir1.string() == CurrDir2);

	spdlog::debug("Testing appending to a path...");
	path AppendTest = CurrDir1;
	auto s = string("/testfile.txt");
	Append(AppendTest, s);
	spdlog::debug("Append test1: {}", AppendTest.string());
	AppendTest = FromCurrentDirectory(s);
	spdlog::debug("Append test2: {}", AppendTest.string());

	spdlog::debug("Testing create directory...");
	auto TestDir = path(CurrDir1.string() + "/TestDirectory/");
	MEPH_ASSERT(DirectoryCreate(TestDir));

	spdlog::debug("Testing create file...");
	auto TestFile = path(TestDir.string() + "testfile.txt");
	fstream stream;
	MEPH_ASSERT(FileCreate(TestFile, stream, true));
	spdlog::debug("Testing write to file...");
	string TestString = "MyTestString";
	stream.write(TestString.c_str(), TestString.length());
	stream.close();

	spdlog::debug("Testing _stat functionality...");
	FileInformation fi;
	MEPH_ASSERT(GetFileInformation(TestFile, fi));

	auto TestFileCopy = path(TestFile.parent_path().string() + "/" + TestFile.stem().string() + ".copy.txt");

	spdlog::debug("Testing path normalize...\n{}\n", FilePathNormalize(TestFileCopy).string());
	spdlog::debug("Testing path normalize absolute...\n{}\n", FilePathNormalize(TestFileCopy, true).string());

	spdlog::debug("Testing file copy...");
	MEPH_ASSERT(FileCopy(TestFile, TestFileCopy));

	spdlog::debug("Testing get file size...");
	MEPH_ASSERT(FileGetSize(TestFileCopy) == TestString.length());

	spdlog::debug("Testing file enumeration...");
	MEPH_ASSERT(FilesIn(TestDir, true).size() == 2);

	spdlog::debug("Testing directory copying...");
	auto TestDirectoryCopy = path(CurrDir1.string() + "/TestDirectory2/");
	MEPH_ASSERT(DirectoryCopy(TestDir, TestDirectoryCopy));
	MEPH_ASSERT(PathExists(TestDirectoryCopy));

	spdlog::debug("Testing file/path deletion...");
	MEPH_ASSERT(PathDelete(TestDir));
	MEPH_ASSERT(PathDelete(TestDirectoryCopy));

	spdlog::debug("ME::Disk test case passed!\n\n"); 
}