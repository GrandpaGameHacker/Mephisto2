#include "IAsset.h"
#include <spdlog/spdlog.h>
IAsset::IAsset()
{

}

IAsset::IAsset(ME::Disk::File file)
{
	if (file.Valid())
	{
		Load();
	}
	else
	{
		spdlog::error("IAsset::IAsset() -> asset {} is invalid!", file.Info.Name);
	}
}

IAsset::~IAsset()
{

}

void IAsset::Load()
{
	switch (File.Mode)
	{
	case ME::Disk::EFileMode::ASCII:
		SData = File.ReadString();
		break;
	
	case ME::Disk::EFileMode::Binary:
		Data = File.Read();
		break;

	case ME::Disk::EFileMode::Unicode:
		WSData = File.ReadUnicodeString();
		break;
	}
}

void IAsset::Reload()
{

}

void IAsset::Unload()
{
	SData.clear();
	WSData.clear();
	Data.reset();
}
