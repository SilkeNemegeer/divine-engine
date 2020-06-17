#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Time.h"
#include "DebugRenderer.h"
#include "ServiceLocator.h"
#include "BaseGame.h"
#include "MaterialManager.h"

using namespace std;
using namespace std::chrono;

bool divengine::Minigin::m_IsRunning = true;

void divengine::Minigin::Quit()
{
	m_IsRunning = false;
}

void divengine::Minigin::Initialize()
{
	Renderer::GetInstance().Init(BaseGame::GetGameSettings().Window);
}

void divengine::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	ServiceLocator::Destroy();

}

void divengine::Minigin::Run()
{
	SceneManager::GetInstance().Initialize();

#ifdef _DEBUG
	DebugRenderer::EnableDebugRendering(true);
#endif // DEBUG

	try
	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		//bool doContinue = true;
		float timeSinceLastFixedUpdate = 0.f;	//update time using fixed timestep (MsPerUpdate = timestep) (lag = totalTime)

		Time::GetInstance().Start();
		while (m_IsRunning)
		{
			//Time::GetInstance().StartFrame();
		
			Time::GetInstance().Update();
			timeSinceLastFixedUpdate += Time::GetInstance().GetDeltaTime();

			if (!input.ProcessInput())
				m_IsRunning = false;

			while (timeSinceLastFixedUpdate >= Time::MS_PER_UPDATE)
			{
				//fixed update triggered
				sceneManager.FixedUpdate();
				//TODO: put collision updates in fixed update
				timeSinceLastFixedUpdate -= Time::MS_PER_UPDATE;
			}
			sceneManager.Update();
			renderer.Render(); //Will always render
			//Time::GetInstance().EndFrame();
		}
	}
	catch(const std::exception& exception)
	{
		std::cout << exception.what() << "\n";
	}
}

divengine::Minigin::Minigin()
{
}

divengine::Minigin::~Minigin()
{
	Cleanup();
}