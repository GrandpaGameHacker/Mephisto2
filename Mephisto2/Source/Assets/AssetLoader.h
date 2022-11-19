#pragma once
#include <memory>
#include <future>
#include <unordered_map>
#include <string>

#include <FileSystem/FileSystem.h>

class IAsset;

class AssetLoader
{
public:
	AssetLoader();
	virtual ~AssetLoader();

	std::shared_ptr<IAsset> Load(std::filesystem::path AssetName, ME::Disk::EFileMode Mode);
	std::future<std::shared_ptr<IAsset>> LoadAsync(std::filesystem::path AssetName, ME::Disk::EFileMode Mode);

	std::unordered_map<std::string, std::shared_ptr<IAsset>> AssetCache;

};