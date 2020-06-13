#pragma once
#include "GameObject.h"
//TODO: use threading here?
#include <functional>

namespace divengine
{
	class Timer : public GameObject
	{
	public:
		void Update() override;
		void Render() const override {};

		Timer(float time, std::function<void()> func = []() {});
		bool IsRunning() const { return m_IsRunning; };
		void Start();
		void SetTime(float time);
		void Stop();

	private:
		bool m_IsRunning;
		std::function<void()> m_CallbackFunc;
		float m_CurrentTime;
		float m_TotalTime;
	};
}
