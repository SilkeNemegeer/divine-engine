#pragma once
#include "Singleton.h"
#include <map>

namespace divengine
{
	class SoundManager : public Singleton<SoundManager>
	{
	public:
		SoundManager(const SoundManager& other) = delete;
		SoundManager(SoundManager&& other) noexcept = delete;
		SoundManager& operator=(const SoundManager& other) = delete;
		SoundManager& operator=(SoundManager&& other) noexcept = delete;
		SoundManager();
		virtual ~SoundManager();

		FMOD::System* GetFmodSystem() const { return m_pFmodSystem; }
		
		FMOD::Sound* LoadSound(const std::string& path, const std::string& soundName, FMOD_MODE mode = FMOD_2D | FMOD_LOOP_OFF);
		FMOD::Sound* LoadStream(const std::string& path, const std::string& streamName, FMOD_MODE mode = FMOD_LOOP_NORMAL);
		bool StartSound(const std::string& soundName, int channelId = -1);
		FMOD::Sound* GetSound(const std::string& soundName);
		
		void AddChannel(FMOD::Channel* pChannel, unsigned int id);
		FMOD::Channel* GetChannel(unsigned int id);

		//Master volume settings
		void SetMasterVolume(float volume);
		float GetMasterVolume() const { return m_MasterVolume; };
		void MuteAll(bool mute);
		bool IsMasterMuted() const { return m_IsMasterMuted; };
		void PauseAll(bool pause);
		bool IsMasterPaused() const { return m_IsAllPaused; };
		FMOD::ChannelGroup* GetMasterChannelGroup() { return m_pMainChannelGroup; };

		static bool CheckResult(FMOD_RESULT result);
		void Update();

	protected:
		friend class Singleton<SoundManager>;

	private:
		void InitializeSystem();

		FMOD::System* m_pFmodSystem = nullptr;
		std::map<std::string, FMOD::Sound*> m_pSounds;
		std::map<unsigned int, FMOD::Channel*> m_pChannels;

		//Master volume settings
		FMOD::ChannelGroup* m_pMainChannelGroup; //Takes care of all sounds
		float m_MasterVolume;
		bool m_IsMasterMuted;
		bool m_IsAllPaused;
	};
}
