#pragma once

namespace viva
{
	class ResourceManager
	{
	private:
		std::map<wstring, Resource*> resources;
	public:
        // Ctor.
		ResourceManager() { }

        // Add resource. No duplicate name allowed. Exception will be thrown.
        // res: resource to add
		void AddResource(Resource* res);

        // Get resource of that name. Returns nullptr if not found.
        // name: search name
		Resource* GetResource(const wstring& name) const;

        // Get texture of that name. Returns nullptr if not found.
        // name: search name
        Texture* GetTexture(const wstring& name) const;

        // Remove resource of that name. Exception thrown if not found.
        // name: search name
		void RemoveResource(const wstring& name);

        // Clear resource manager. It does not destroy anything.
		void RemoveAll();
	};
}
