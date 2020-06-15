#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace divengine;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene()
{
	for (auto pObject : m_Objects)
	{
		SAFEDELETE(pObject);
	}
}

void Scene::AddObject(GameObject* object)
{
	m_Objects.push_back(object);
}

void divengine::Scene::AddRigidbody(Rigidbody*rigidBody)
{
	m_pRigidbodies.push_back(rigidBody);
}

void divengine::Scene::AddCollider(ColliderComponent* pCollider)
{
	m_pColliders.push_back(pCollider);
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
	for (const auto& object : m_Objects)
	{
		object->Initialize();
	}
}

