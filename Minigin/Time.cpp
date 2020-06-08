#include "MiniginPCH.h"
#include "Time.h"
#include <math.h>
#include <thread>

const float Time::MS_PER_UPDATE = 0.02f;
const float Time::FPS = 60.f;

Time::Time()
	:m_DeltaTime{0.f}
	,m_FixedDeltaTime{0.f}
	,m_Fps{0}
	,m_FPSTimer{0.f}
	,m_Frames{0}
	,m_LastTime{}
{

}

void Time::SetDeltaTime(float deltaTime)
{
	m_DeltaTime = deltaTime;
}

//Happens once per frame
void Time::Update()
{
	m_CurrentTime = high_resolution_clock::now();

	m_DeltaTime = (duration_cast<duration<float>>(m_CurrentTime - m_LastTime).count());
	int sleepTime = int(std::roundf(((1 /FPS) - m_DeltaTime) * 1000000));
	std::this_thread::sleep_for(microseconds(sleepTime));
	m_DeltaTime += (sleepTime / 1000000.f);

	m_LastTime = m_CurrentTime;

	//Update fps
	m_FPSTimer += m_DeltaTime;
	m_Frames++;
	if (m_FPSTimer >= m_MaxFPSInterval)
	{
		m_Fps = (int)std::roundf(m_Frames / m_FPSTimer);
		m_FPSTimer = 0.f;
		m_Frames = 0;
	}
}

int Time::GetFps() const
{
	return m_Fps;
}

void Time::Start()
{
	m_LastTime = std::chrono::high_resolution_clock::now();
}

void Time::StartFrame()
{
	m_StartFrameTime = std::chrono::high_resolution_clock::now();
}

void Time::EndFrame()
{

}