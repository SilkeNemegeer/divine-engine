#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "Debug.h"
#include <algorithm>
#include "ColliderComponent.h"
#include "RigidbodyComponent.h"

using namespace divengine;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name){}

Scene::~Scene()
{
	for (auto pObject : m_ObjectsToDelete)
	{
		SAFEDELETE(pObject);
	}

	for (auto pObject : m_Objects)
	{
		SAFEDELETE(pObject);
	}
}

void Scene::AddObject(GameObject* object)
{
	m_Objects.push_back(object);
}

void divengine::Scene::DestroyObject(GameObject* pObject)
{
	const auto it = std::find(m_Objects.begin(), m_Objects.end(), pObject);

#if _DEBUG
	if (it == m_Objects.end())
	{
		Debug::LogWarning("Scene::DestroyObject: GameObject to remove is not in this scene!");
		return;
	}
#endif

//	m_Objects.erase(it);
	pObject->SetActive(false);
	m_ObjectsToDelete.push_back(pObject);
}

std::vector<GameObject*> divengine::Scene::FindObjectsWithTag(const std::string& tag)
{
	std::vector<GameObject*> objects;

	for (auto pObject : m_Objects)
	{
		if (strcmp(pObject->GetTag().c_str(), tag.c_str()) == 0)
			objects.push_back(pObject);
	}

	return objects;
}

void divengine::Scene::AddCollider(ColliderComponent* pCollider)
{
	const auto it = std::find(m_pColliders.begin(), m_pColliders.end(), pCollider);
	if(it == m_pColliders.end())
		m_pColliders.push_back(pCollider);
}

void divengine::Scene::RemoveCollider(ColliderComponent* pCollider)
{
	auto it = std::find(m_pColliders.begin(), m_pColliders.end(), pCollider);
	if (it == m_pColliders.end())
	{
		Debug::LogWarning("Cannot remove collider that is not in the scene");
		return;
	}

	m_pColliders.erase(it);
}

std::string divengine::Scene::Name() const
{
	return m_Name;
}

void Scene::Update()
{
	for(auto& object : m_Objects)
	{
		object->Update();
	}

	for (size_t i = 0; i < m_ObjectsToDelete.size(); i++)
	{
		auto rigidbody = m_ObjectsToDelete[i]->GetComponent<RigidbodyComponent>();
		if (rigidbody)
		{
			RemoveCollider(rigidbody->GetCollider());
			for (auto collider : m_pColliders)
			{
				collider->GetRigidBody()->RemoveCollider(rigidbody->GetCollider());
			}
		}
		m_Objects.erase(std::remove(m_Objects.begin(), m_Objects.end(), m_ObjectsToDelete[i]), m_Objects.end());
		SAFEDELETE(m_ObjectsToDelete[i]);
	}
	m_ObjectsToDelete.clear();
}

void divengine::Scene::FixedUpdate()
{
	//Do collisions for the rigidbodies
	//for (const auto& rigidbody : m_pRigidbodies)
	//{
	//	
	//}

}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

void divengine::Scene::InitializeAll() const
{
	//for (const auto& object : m_Objects)
	//{
	//	object->Initialize();

	//}

	for (size_t i = 0; i < m_Objects.size(); i++)
	{
		m_Objects[i]->Initialize();
	}
}

void divengine::Scene::Start() const
{
	for (size_t i = 0; i < m_Objects.size(); i++)
	{
		m_Objects[i]->Start();
	}
}

