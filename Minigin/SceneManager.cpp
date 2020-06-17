#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Debug.h"

void divengine::SceneManager::Update()
{
	m_pCurrentScene->Update();
}

void divengine::SceneManager::FixedUpdate()
{
	m_pCurrentScene->FixedUpdate();
}

void divengine::SceneManager::Render()
{
	//ImGui::ShowDemoWindow();
	m_pCurrentScene->Render();
}

void  divengine::SceneManager::Initialize()
{
	for (const auto& scene : m_Scenes)
	{
		scene->InitializeAll();
	}
	//m_pCurrentScene->InitializeAll();
}

void divengine::SceneManager::SetAsCurrentScene(const std::string& name)
{
	//Find the first scene with the corresponding name
	for (const auto& scene : m_Scenes)
	{
		if (scene->Name() == name)
		{
			m_pCurrentScene = scene;
			scene->Start();
			//scene->InitializeAll();
			return;
		}
	}
}

std::shared_ptr<divengine::Scene> divengine::SceneManager::GetSceneByName(const std::string& name) const
{
	auto it = std::find_if(m_Scenes.begin(), m_Scenes.end(), [name](std::shared_ptr<Scene> pScene) {return pScene->Name() == name; });
	if (it == m_Scenes.end())
	{
		Debug::LogWarning("Could not find scene with name ", name.c_str());
		return nullptr;
	}
	return *it;
}

divengine::Scene& divengine::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);

	//Set this scene as the current if it wasn't set
	if(!m_pCurrentScene)
		m_pCurrentScene = scene;
	return *scene;
}

void divengine::SceneManager::AddScene(std::shared_ptr<Scene> scene)
{
	if (std::find(m_Scenes.begin(), m_Scenes.end(), scene) != m_Scenes.end())
		return;

	m_Scenes.push_back(scene);
	if (!m_pCurrentScene)
		m_pCurrentScene = scene;
}
