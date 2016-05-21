#pragma once

namespace viva
{
	class ResourceManager
	{
	private:
		map<wstring, Resource*> resources;
		ResourceManager() { }
		//void ThrowUninitialized();
	public:
		// cannot construct singleton
		ResourceManager(ResourceManager const&) = delete;

		//cannot assign to singleton
		void operator=(ResourceManager const&) = delete;

		static ResourceManager& Get();

		void AddResource(Resource* res);

		Resource* GetResource(const wstring& name) const;

		void RemoveResource(const wstring& name);

		void RemoveAll();
	};
}
