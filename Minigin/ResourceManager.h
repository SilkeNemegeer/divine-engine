#pragma once
#include "Singleton.h"

namespace divengine
{
	class Texture2D;
	class Font;
	class ResourceManager final //: public Singleton<ResourceManager>
	{
	public:
		ResourceManager() = default;

		void Init(const std::string& data);
		std::shared_ptr<Texture2D> LoadTexture(const std::string& file) const;
		std::shared_ptr<Font> LoadFont(const std::string& file, unsigned int size) const;
		const std::string GetFullDataPath(const std::string& relativePath) const;

	private:
		//friend class Singleton<ResourceManager>;
		//ResourceManager() = default;
		std::string m_DataPath;
	};
}
