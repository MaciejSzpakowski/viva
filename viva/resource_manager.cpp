#include <viva/viva.h>

namespace viva
{
	void ResourceManager::AddResource(Resource* res)
	{
		auto it = resources.find(res->GetName());

        if (it != resources.end())
            throw Error("ResourceManager::AddResource()", "Resource of that name already exists");

		res->_SetCached(true);
		resources[res->GetName()] = res;
	}

	Resource* ResourceManager::GetResource(const wstring& name) const
	{
        auto it = resources.find(name);

        if (it == resources.end())
            return nullptr;

		return it->second;
	}

    Texture* ResourceManager::GetTexture(const wstring& name) const
    {
        auto it = resources.find(name);

        if (it == resources.end() || it->second->GetType() != Resource::Type::Texture)
            return nullptr;

        return (Texture*)it->second;
    }

	void ResourceManager::RemoveResource(const wstring& name)
	{
		auto it = resources.find(name);

        if (it == resources.end())
            throw Error("ResourceManager::RemoveResource()", "Resource not found");

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