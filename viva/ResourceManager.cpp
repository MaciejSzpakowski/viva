#include "Proto.h"

namespace viva
{
	ResourceManager& ResourceManager::Get()
	{
		static ResourceManager instance;
		return instance;
	}

	void ResourceManager::ThrowUninitialized()
	{
		if (!initialized)
			throw std::runtime_error("ResourceManager is not initialized");
	}

	void ResourceManager::AddTexture(Texture* texture)
	{
		auto it = textures.find(texture->GetName());

		if (it != textures.end())
			throw std::runtime_error("ResourceManager::AddTexture()\nTexture of that name already exists");

		texture->_SetCached(true);
		textures[texture->GetName()] = texture;
	}

	Texture* ResourceManager::GetTexture(const wstring& name) const
	{
		auto it = textures.find(name);

		if (it == textures.end())
			throw std::runtime_error("ResourceManager::GetTexture()\nTexture not found");

		return it->second;
	}

	void ResourceManager::RemoveTexture(const wstring& name)
	{
		auto it = textures.find(name);

		if (it == textures.end())
			throw std::runtime_error("ResourceManager::RemoveTexture()\nTexture not found");

		it->second->_SetCached(false);
		textures.erase(it);
	}
}