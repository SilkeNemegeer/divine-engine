#pragma once
#include "BaseComponent.h"
#include <string>

namespace divengine
{
	class TextComponent;
	class FPSComponent : public BaseComponent
	{
		//Keeps track of the fps (frames per second) ~ (Lag / MsPerUpdate)
		//Fps = 1 / deltaTime
	public:
		FPSComponent();
		virtual ~FPSComponent() = default;
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;
		int GetFPS() const;

	protected:
		void Update() override;
		void Initialize() override;
		void Render() override;

	private:
		TextComponent* m_pTextComponent;
		int m_FPS;
		float m_FPSTimer;
		float m_MaxTime;
	};
}
