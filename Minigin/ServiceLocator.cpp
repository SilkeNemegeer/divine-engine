#include "MiniginPCH.h"
#include "ServiceLocator.h"
#include "SoundManager.h"
#include "ResourceManager.h"

divengine::SoundManager* divengine::ServiceLocator::soundManager = nullptr;
divengine::ResourceManager* divengine::ServiceLocator::resourceManager = nullptr;

void divengine::ServiceLocator::Init()
{
	soundManager = new SoundManager();
	resourceManager = new ResourceManager();
}

void divengine::ServiceLocator::Destroy()
{
	SAFEDELETE(soundManager);
	SAFEDELETE(resourceManager);
}