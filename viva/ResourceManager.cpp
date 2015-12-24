#include "Viva.h"

namespace viva
{
	ResourceManager& ResourceManager::Get()
	{
		static ResourceManager instance;
		return instance;
	}

	/*void ResourceManager::ThrowUninitialized()
	{
		if (!initialized)
			throw std::runtime_error("ResourceManager is not initialized");
	}*/

	void ResourceManager::AddResource(Resource* res)
	{
		auto it = resources.find(res->GetName());

		if (it != resources.end())
			throw std::runtime_error("ResourceManager::AddResource()\nResource of that name already exists");

		res->_SetCached(true);
		resources[res->GetName()] = res;
	}

	Resource* ResourceManager::GetResource(const wstring& name) const
	{
		auto it = resources.find(name);

		if (it == resources.end())
			throw std::runtime_error("ResourceManager::GetResource()\nResource not found");

		return it->second;
	}

	void ResourceManager::RemoveResource(const wstring& name)
	{
		auto it = resources.find(name);

		if (it == resources.end())
			throw std::runtime_error("ResourceManager::RemoveResource()\nResource not found");

		it->second->_SetCached(false);
		resources.erase(it);
	}

	void ResourceManager::RemoveAll()
	{
		for (auto& r : resources)
			r.second->_SetCached(false);

		resources.clear();
	}
}