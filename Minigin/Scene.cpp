#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::AddObject(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
}

std::string dae::Scene::Name() const
{
	return m_Name;
}

void Scene::Update(float MsPerUpdate)
{
	for(auto& object : m_Objects)
	{
		object->Update(MsPerUpdate);
	}
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

