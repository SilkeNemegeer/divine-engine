#pragma once
#include "Singleton.h"
#include <string>
#include <vector>
#include <iostream>

namespace divengine
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);
		void AddScene(std::shared_ptr<Scene> scene);

		void Update();
		void FixedUpdate();
		void Render();
		void Initialize();

		void SetAsCurrentScene(const std::string& name);
		std::shared_ptr<Scene> GetCurrentScene() const { return m_pCurrentScene; };
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		std::shared_ptr<Scene> m_pCurrentScene = nullptr;
	};
}
