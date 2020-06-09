#pragma once
#include "SoundManager.h"
#include "ResourceManager.h"

namespace divengine
{
	class ServiceLocator
	{
	public:
		static void Init();
		static SoundManager& GetSoundManager() { return soundManager; };
		static ResourceManager& GetResourceManager() { return resourceManager; };
		
	private:
		static SoundManager soundManager;
		static ResourceManager resourceManager;
	};
}
