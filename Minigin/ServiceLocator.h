#pragma once


namespace divengine
{
	class SoundManager;
	class ResourceManager;
	class ServiceLocator
	{
	public:
		static void Init();
		static SoundManager* GetSoundManager() { return soundManager; };
		static ResourceManager* GetResourceManager() { return resourceManager; };
		static void Destroy();
		
	private:
		static SoundManager* soundManager;
		static ResourceManager* resourceManager;
	};
}
