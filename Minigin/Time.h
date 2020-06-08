#pragma once
#include "Singleton.h"
#include <chrono>

using namespace std::chrono;

class Time final : public divengine::Singleton<Time>
{
public:
	Time();
	float GetDeltaTime() const { return m_DeltaTime; };
	float GetFixedDeltaTime() const { return m_FixedDeltaTime; };
	void SetDeltaTime(float deltaTime);
	void Update();
	int GetFps() const;
	void Start();
	void StartFrame();
	void EndFrame();
	static const float MS_PER_UPDATE; //MsPerFrame 16 for 60 fps, 33 for 30 fps
	static const float FPS; //MsPerFrame 16 for 60 fps, 33 for 30 fps

protected:

private:
	//const float m_MsPerFrame;
	float m_FixedDeltaTime;
	float m_DeltaTime;

	//FPS
	int m_Fps;
	float m_FPSTimer;
	const float m_MaxFPSInterval = 0.5f;
	int m_Frames;

	std::chrono::time_point < std::chrono::steady_clock > m_LastTime;
	std::chrono::time_point<std::chrono::steady_clock> m_CurrentTime;

	std::chrono::time_point < std::chrono::steady_clock > m_StartFrameTime;
};

