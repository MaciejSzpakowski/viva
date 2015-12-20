#pragma once

namespace viva
{
	class ResourceManager
	{
	private:
		map<wstring, Resource*> resources;
		bool initialized;
		ResourceManager() { initialized = false; }
		void ThrowUninitialized();
	public:
		static ResourceManager& Get();

		void AddResource(Resource* res);

		Resource* GetResource(const wstring& name) const;

		void RemoveResource(const wstring& name);

		void RemoveAll();
	};
}
