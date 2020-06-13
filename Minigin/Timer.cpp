#include "MiniginPCH.h"
#include "Timer.h"
#include "Time.h"

divengine::Timer::Timer(float time, std::function<void()> func)
	:m_TotalTime{time}
	,m_CurrentTime{0.f}
	,m_IsRunning{false}
	,m_CallbackFunc{func}
{
}

void divengine::Timer::Start()
{
	m_IsRunning = true;
	m_CurrentTime = 0.f;
}

void divengine::Timer::Update()
{
	if (m_IsRunning)
	{
		m_CurrentTime += Time::GetInstance().GetDeltaTime();
		if (m_CurrentTime >= m_TotalTime)
		{
			m_IsRunning = false;
			m_CallbackFunc();
		}
	}
}

void divengine::Timer::SetTime(float time)
{
	m_TotalTime = time;
}

void divengine::Timer::Stop()
{
	m_IsRunning = false;
}
