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
		void DestroyObject(GameObject* pObject);
		void AddCollider(ColliderComponent* pCollider);
		void RemoveCollider(ColliderComponent* pCollider);
		std::string Name() const;

		std::vector<ColliderComponent*>GetColliders() const{ return m_pColliders; };
		void Update();
		void FixedUpdate();
		void Render() const;
		void InitializeAll() const;
		void Start() const;
		size_t GetGameObjectCount() const { return m_Objects.size(); };
		const std::vector<GameObject*>& GameObjects() const { return m_Objects; };

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);
		std::string m_Name;
		std::vector <GameObject*> m_Objects{};
		std::vector<GameObject*> m_ObjectsToDelete{};
		std::vector<ColliderComponent*>m_pColliders{};
		static unsigned int m_IdCounter; 
	};

}
