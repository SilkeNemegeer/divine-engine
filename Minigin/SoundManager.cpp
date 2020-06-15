#include "MiniginPCH.h"
#include "SoundManager.h"
#include "ResourceManager.h"
#include "Debug.h"
#include "ServiceLocator.h"

divengine::SoundManager::SoundManager()
	:m_pFmodSystem{}
	,m_pSounds{}
	,m_pChannels{}
	,m_pMainChannelGroup{}
	,m_MasterVolume{}
{
	InitializeSystem();
	FMOD_RESULT result = m_pFmodSystem->createChannelGroup("AllSounds", &m_pMainChannelGroup);
	CheckResult(result);
}

divengine::SoundManager::~SoundManager()
{
	for (auto pSound : m_pSounds)
	{
		pSound.second->release();
	}

	m_pMainChannelGroup->release();

	if (m_pFmodSystem)
	{
		m_pFmodSystem->release();
	}
}

FMOD::Sound* divengine::SoundManager::LoadSound(const std::string& path, const std::string& soundName, FMOD_MODE mode)
{
	if (m_pSounds.find(soundName) != m_pSounds.end())
		return nullptr;

	//Create new sound
	FMOD::Sound* pSound = nullptr;
	FMOD_RESULT result = m_pFmodSystem->createSound(ServiceLocator::GetResourceManager()->GetFullDataPath(path).c_str(), mode, 0, &pSound);
	//FMOD_RESULT result = m_pFmodSystem->createSound(ResourceManager::GetInstance().GetFullDataPath(path).c_str(), mode, 0, &pSound);

	if (!CheckResult(result))
		return nullptr;

	m_pSounds[soundName] = pSound;
	if (pSound != nullptr)
	{
		return pSound;
	}
	return nullptr;
}

FMOD::Sound* divengine::SoundManager::LoadStream(const std::string& path, const std::string& streamName, FMOD_MODE mode)
{
	if (m_pSounds.find(streamName) != m_pSounds.end())
		return nullptr;

	//Create new sound
	FMOD::Sound* pStream = nullptr;
	FMOD_RESULT result = m_pFmodSystem->createStream(path.c_str(), mode, 0, &pStream);

	if (!CheckResult(result))
		return nullptr;

	m_pSounds[streamName] = pStream;
	if (pStream != nullptr)
		return pStream;

	return nullptr;
}

bool divengine::SoundManager::StartSound(const std::string& soundName, int channelId) //Choose channel where to play if wanted
{
	if (m_pSounds.find(soundName) == m_pSounds.end())
	{
		Debug::LogWarning("SoundManager::StartSound: Sound does not exist");
		return false;
	}
	
	//FMOD::Channel* pChannel = (channelId == -1) ? 0 : GetChannel(unsigned int(channelId));
	FMOD_RESULT result;
	if (channelId < 0)
	{
		 result = m_pFmodSystem->playSound(m_pSounds[soundName], m_pMainChannelGroup, false, &m_pChannels[channelId]);
	}
	else
	{
		result = m_pFmodSystem->playSound(m_pSounds[soundName], m_pMainChannelGroup, false, &m_pChannels[channelId]);
	}
	if (!CheckResult(result))
		return false;

	return true;
}

FMOD::Sound* divengine::SoundManager::GetSound(const std::string& soundName)
{
	if (m_pSounds.find(soundName) == m_pSounds.end())
	{
		Debug::LogWarning("SoundManager::GetSound: Sound does not exist");
		return nullptr;
	}

	return m_pSounds[soundName];
}

void divengine::SoundManager::AddChannel(unsigned int id)
{
	if (m_pChannels.find(id) != m_pChannels.end())
	{
		Debug::LogWarning("SoundManager::AddChannel: This id already has a channel!");
		return;
	}

	m_pChannels[id] = nullptr;
}

FMOD::Channel* divengine::SoundManager::GetChannel(unsigned int id)
{
	if (m_pChannels.find(id) == m_pChannels.end())
	{
		Debug::LogWarning("SoundManager::GetChannel: Channel with id ", id , " not found");
		return nullptr;
	}
	
	return m_pChannels[id];
}

void divengine::SoundManager::SetMasterVolume(float volume)
{
	m_pMainChannelGroup->setVolume(volume);
	m_MasterVolume = volume;
}

void divengine::SoundManager::MuteAll(bool mute)
{
	m_pMainChannelGroup->setMute(mute);
	m_IsMasterMuted = mute;
}

void divengine::SoundManager::PauseAll(bool pause)
{
	m_pMainChannelGroup->setPaused(pause);
	m_IsAllPaused = pause;
}

bool divengine::SoundManager::CheckResult(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		Debug::LogWarning("FMOD error: ", result, FMOD_ErrorString(result));
		return false;
	}
	return true;
}

void divengine::SoundManager::Update()
{
	FMOD_RESULT result = m_pFmodSystem->update();
	CheckResult(result);
}

void divengine::SoundManager::InitializeSystem()
{
	//Creating the fmod system
	FMOD_RESULT result = FMOD::System_Create(&m_pFmodSystem);
	CheckResult(result);

	unsigned int version = 0;
	result = m_pFmodSystem->getVersion(&version);
	CheckResult(result);

	if (version < FMOD_VERSION)
	{
		Debug::LogWarning("SoundManager::Initialize: error, using an old version of fmod!");
		return;
	}

	int numDrivers = 0;
	result = m_pFmodSystem->getNumDrivers(&numDrivers);
	CheckResult(result);

	if (numDrivers == 0)
	{
		result = m_pFmodSystem->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
		CheckResult(result);
	}
	else
	{
		result = m_pFmodSystem->init(32, FMOD_INIT_NORMAL, nullptr);
		CheckResult(result);
	}
}
