#include <spdlog/spdlog.h>
#include <Core/MephistoAssert.h>
#include <FileSystem/FileSystem.h>

using namespace std::filesystem;
using namespace std;

bool ME::Disk::GetFileInformation(std::filesystem::path& file, FileInformation& fileInfo)
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

std::filesystem::path ME::Disk::CurrentDirectory()
{
	return current_path();
}

bool ME::Disk::DirectoryCreate(const std::filesystem::path& dir)
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

bool ME::Disk::DirectoryCopy(const std::filesystem::path& source, const std::filesystem::path& destination)
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

bool ME::Disk::PathExists(const std::filesystem::path& file_or_dir)
{
	return exists(file_or_dir);
}

bool ME::Disk::PathDelete(const std::filesystem::path& to_delete)
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

bool ME::Disk::FileCreate(const std::filesystem::path& file, fstream& stream, bool bOverwrite)
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

bool ME::Disk::FileCopy(const std::filesystem::path& source, const std::filesystem::path& destination)
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

uint64_t ME::Disk::FileGetSize(const std::filesystem::path& file)
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

std::vector<std::filesystem::path> ME::Disk::FilesIn(const std::filesystem::path & dir, bool bRecursive)
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

std::filesystem::path ME::Disk::FilePathNormalize(std::filesystem::path& file, bool bAbsolute)
{
	std::filesystem::path RelPath;
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

void ME::Disk::Append(std::filesystem::path& a, std::filesystem::path& b)
{
	a = std::filesystem::path(a.string() + b.string());
}

void ME::Disk::Append(std::filesystem::path& a, std::string& b)
{
	a = std::filesystem::path(a.string() + b);
}


std::filesystem::path ME::Disk::FromCurrentDirectory(std::filesystem::path& a)
{
	std::filesystem::path p = CurrentDirectory();
	Append(p, a);
	return p;
}

std::filesystem::path ME::Disk::FromCurrentDirectory(const char* a)
{
	auto p = std::string(a);
	return FromCurrentDirectory(p);
}

std::filesystem::path ME::Disk::FromCurrentDirectory(std::string & a)
{
	std::filesystem::path p = CurrentDirectory();
	Append(p, a);
	return p;
}


std::string ME::Disk::CurrentDirectoryToString()
{
	return current_path().string();
}

bool ME::Disk::DirectoryCreate(const std::string& dir)
{
	return DirectoryCreate(std::filesystem::path(dir));
}


bool ME::Disk::DirectoryCopy(const std::string& source, const std::string& destination)
{
	return DirectoryCopy(std::filesystem::path(source), path(destination));
}

bool ME::Disk::PathExists(const std::string& file_or_dir)
{
	return PathExists(path(file_or_dir));
}

bool ME::Disk::PathDelete(const std::string& to_delete)
{
	return PathDelete(path(to_delete));
}

bool ME::Disk::FileCreate(const std::string& file, std::fstream& stream, bool bOverwrite)
{
	return FileCreate(path(file), stream, bOverwrite);
}

bool ME::Disk::FileCopy(const std::string& src, const std::string& dest)
{
	return FileCopy(path(src), path(dest));
}

uint64_t ME::Disk::FileGetSize(const std::string& file)
{
	return FileGetSize(path(file));
}

std::vector<std::string> ME::Disk::FilesIn(const std::string& dir, bool bRecursive)
{
	std::vector<std::string> found;
	if (!bRecursive)
	{
		for (const auto& item : directory_iterator(dir))
		{
			std::string item_path = path(item).string();
			found.push_back(item_path);
		}
	}
	else
	{
		for (const auto& item : recursive_directory_iterator(dir))
		{
			std::string item_path = path(item).string();
			found.push_back(item_path);
		}
	}
	return found;
}

std::string ME::Disk::FilePathNormalize(std::string& file, bool bAbsolute)
{
	auto PathFile = std::filesystem::path(file);
	auto PathResult = FilePathNormalize(PathFile, bAbsolute);
	return PathResult.string();
}


void ME::Disk::internal::ProcessError(const std::string& function_name, filesystem_error& exception)
{
	auto code = exception.code();
	spdlog::error("ME::Disk::{} Exception: {} : {}", function_name, exception.what(), code.message());
}

void ME::Disk::internal::TestAll()
{
	spdlog::debug("Running All ME::Disk Tests... (Filesystem.cpp)");

	spdlog::debug("Testing getting current directory...");
	std::filesystem::path CurrDir1 = CurrentDirectory();
	std::string CurrDir2 = CurrentDirectoryToString();
	MEPH_ASSERT(CurrDir1.string() == CurrDir2);

	spdlog::debug("Testing appending to a path...");
	std::filesystem::path AppendTest = CurrDir1;
	auto s = std::string("/testfile.txt");
	Append(AppendTest, s);
	spdlog::debug("Append test1: {}", AppendTest.string());
	AppendTest = FromCurrentDirectory(s);
	spdlog::debug("Append test2: {}", AppendTest.string());

	spdlog::debug("Testing create directory...");
	auto TestDir = std::filesystem::path(CurrDir1.string() + "/TestDirectory/");
	MEPH_ASSERT(DirectoryCreate(TestDir));

	spdlog::debug("Testing create file...");
	auto TestFile = std::filesystem::path(TestDir.string() + "testfile.txt");
	std::fstream stream;
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

ME::Disk::File::File(){}

ME::Disk::File::File(std::filesystem::path path, bool bOverwrite)
{
	Path = path;
	this->bOverwrite = bOverwrite;
	GetFileInformation(path, Info);
	Open();
}

ME::Disk::File::~File()
{
	Close();
}

bool ME::Disk::File::Open()
{
	if (!bOpened)
	{
		FileCreate(Path, Stream, bOverwrite);
		bOpened = Stream.is_open();
		return bOpened;
	}
	return false;
}

void ME::Disk::File::Close()
{
	if (bOpened || Stream.is_open())
	{
		Stream.close();
		bOpened = Stream.is_open();
	}
}

void ME::Disk::File::Write(uint8* data, size_t length)
{
	MEPH_ASSERT(data);
	if (bOpened)
	{
		Stream.write((const char*) data, length);
	}
	else if (Open())
	{
		Stream.write((const char*) data, length);
	}
	spdlog::error("File::Write() -> tried to write to a inacessable file");
}

void ME::Disk::File::Write(char* data, size_t length)
{
	MEPH_ASSERT(data);
	if (bOpened)
	{
		Stream.write(data, length);
	}
	else if (Open())
	{
		Stream.write(data, length);
	}
	spdlog::error("File::Write() -> tried to write to a inacessable file");
}

void ME::Disk::File::Write(std::string& data)
{
	if (bOpened)
	{
		Stream.write(data.c_str(), data.length());
	}
	else if(Open())
	{
		Stream.write(data.c_str(), data.length());
	}
	spdlog::error("File::Write() -> tried to write to a inacessable file");
}

std::shared_ptr<uint8[]> ME::Disk::File::Read()
{
	if (!bOpened || !Info.SizeInBytes) return nullptr;

	auto data = make_shared<uint8[]>(Info.SizeInBytes);
	Stream.read((char*)data.get(), Info.SizeInBytes);
	return data;
}

std::shared_ptr<uint8[]> ME::Disk::File::Read(size_t length)
{
	if (!bOpened || !Info.SizeInBytes) return nullptr;
	if (length > Info.SizeInBytes) return Read();

	auto data = make_shared<uint8[]>(length);
	Stream.read((char*)data.get(), length);
	return data;
}

std::string ME::Disk::File::ReadString()
{
	std::string outString;
	if (!bOpened) return outString;

	std::string lineContent;
	while (std::getline(Stream, lineContent))
	{
		outString.append(lineContent + "\n");
	}
	return outString;
}
