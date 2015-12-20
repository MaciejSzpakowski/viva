#pragma once

namespace viva
{
	class ResourceManager
	{
	private:
		map<wstring, Texture*> textures;
		bool initialized;
		ResourceManager() { initialized = false; }
		void ThrowUninitialized();
	public:
		static ResourceManager& Get();

		void AddTexture(Texture* texture);

		Texture* GetTexture(const wstring& name) const;

		void RemoveTexture(const wstring& name);
	};
}
