#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update(float MsPerUpdate)
{
	m_pCurrentScene->Update(MsPerUpdate);
}

void dae::SceneManager::Render()
{
	m_pCurrentScene->Render();
}

void dae::SceneManager::SetAsCurrentScene(const std::string& name)
{
	//Find the first scene with the corresponding name
	for (const auto& scene : m_Scenes)
	{
		if (scene->Name() == name)
		{
			m_pCurrentScene = scene;
			return;
		}
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);

	//Set this scene as the current if it wasn't set
	if(!m_pCurrentScene)
		m_pCurrentScene = scene;
	return *scene;
}
