#pragma once
#include "SceneManager.h"

namespace divengine
{
	class GameObject;
	class Rigidbody;
	class ColliderComponent;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void AddObject(GameObject* object);
		void AddRigidbody(Rigidbody* pRigidboy);
		void AddCollider(ColliderComponent* pCollider);
		std::string Name() const;

		std::vector<ColliderComponent*>GetColliders() const{ return m_pColliders; };
		void Update();
		void FixedUpdate();
		void Render() const;
		void InitializeAll() const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);
		std::string m_Name;
		std::vector <GameObject*> m_Objects{};
		std::vector<Rigidbody*>m_pRigidbodies{};
		std::vector<ColliderComponent*>m_pColliders{};
		static unsigned int m_IdCounter; 
	};

}
