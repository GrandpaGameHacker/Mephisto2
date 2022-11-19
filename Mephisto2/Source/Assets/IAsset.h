#pragma once
#include <FileSystem/FileSystem.h>
#include <memory>
class IAsset
{
public:
	IAsset();
	IAsset(ME::Disk::File file);
	virtual ~IAsset();
	virtual void Load();
	virtual void Reload();
	virtual void Unload();
private:

	ME::Disk::File File;
	
	std::shared_ptr<uint8[]> Data;
	std::string SData;
	std::wstring WSData;
};