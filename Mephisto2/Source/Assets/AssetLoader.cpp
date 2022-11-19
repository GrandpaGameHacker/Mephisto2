#include <Assets/AssetLoader.h>
#include <Core/IApplication.h>
#include <FileSystem/FileSystem.h>
#include <Assets/IAsset.h>

AssetLoader::AssetLoader()
{

}

AssetLoader::~AssetLoader()
{
}

std::shared_ptr<IAsset> AssetLoader::Load(std::filesystem::path AssetName, ME::Disk::EFileMode Mode)
{
	std::shared_ptr<IAsset> NewAsset = nullptr;
	std::filesystem::path AbsolutePath = ME::Disk::CurrentDirectory();
	ME::Disk::Append(AbsolutePath, AssetName);

	if (ME::Disk::PathExists(AbsolutePath))
	{
		ME::Disk::File file = ME::Disk::File(AbsolutePath, Mode, true);
		std::shared_ptr<IAsset> NewAsset = std::make_shared<IAsset>();
	}

	return NewAsset;
}

std::future<std::shared_ptr<IAsset>> AssetLoader::LoadAsync(std::filesystem::path AssetName, ME::Disk::EFileMode Mode)
{
	return IApplication::ThrdPool.execute([=]
		{
			return Load(AssetName, Mode);
		});
}
