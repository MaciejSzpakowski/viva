#include "viva.h"

namespace viva
{
    class ResourceManager
    {
    private:
        std::map<wstring, Resource*> resources;
    public:
        // Ctor.
        ResourceManager() 
        { 
        }

        // Add resource. No duplicate name allowed. Exception will be thrown.
        // res: resource to add
        void AddResource(Resource* res)
        {
            auto it = resources.find(res->GetName());

            if (it != resources.end())
                throw Error("ResourceManager::AddResource()", "Resource of that name already exists");

            res->_SetCached(true);
            resources[res->GetName()] = res;
        }

        // Get resource of that name. Returns nullptr if not found.
        // name: search name
        Resource* GetResource(const wstring& name) const
        {
            auto it = resources.find(name);

            if (it == resources.end())
                return nullptr;

            return it->second;
        }

        // Get texture of that name. Returns nullptr if not found.
        // name: search name
        Texture* GetTexture(const wstring& name) const
        {
            auto it = resources.find(name);

            if (it == resources.end() || it->second->GetType() != ResourceType::Texture)
                return nullptr;

            return (Texture*)it->second;
        }

        // Remove resource of that name. Exception thrown if not found.
        // name: search name
        void RemoveResource(const wstring& name)
        {
            auto it = resources.find(name);

            if (it == resources.end())
                throw Error("ResourceManager::RemoveResource()", "Resource not found");

            it->second->_SetCached(false);
            resources.erase(it);
        }

        // Clear resource manager. It does not destroy anything.
        void RemoveAll()
        {
            for (auto& r : resources)
                r.second->_SetCached(false);

            resources.clear();
        }

        void _Destroy()
        {
            RemoveAll();
            delete this;
        }
    };
}
