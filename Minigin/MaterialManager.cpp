#include "MiniginPCH.h"
#include "MaterialManager.h"
#include "Debug.h"
divengine::MaterialManager::MaterialManager()
	:m_pMaterials(std::map< int, PhysicsMaterial2D*>())
{
}

divengine::MaterialManager::~MaterialManager()
{
	for (auto pMaterial : m_pMaterials)
	{
		SAFEDELETE(pMaterial.second);
	}
	m_pMaterials.clear();
}
void divengine::MaterialManager::AddMaterial(PhysicsMaterial2D* pMaterial, int id)
{
	if (pMaterial == nullptr)
	{
		Debug::LogWarning("MaterialManager::AddMaterial: material is null!");
		return;
	}

	for (auto material : m_pMaterials)
	{
		if (material.first == id)
		{
			Debug::LogWarning("MaterialManager::AddMaterial: id is already used!");
			return;
		}

		if (material.second == pMaterial)
		{
			Debug::LogWarning("MaterialManager::AddMaterial: material is already in manager!");
			return;
		}
	}

	m_pMaterials[id] = pMaterial;
}
void divengine::MaterialManager::RemoveMaterial(int id)
{
	auto it = m_pMaterials.find(id);
	if (it == m_pMaterials.end())
	{
		Debug::LogWarning("MaterialManager::RemoveMaterial: Material with id ", id, "not found");
		return;
	}

	SAFEDELETE(it->second);
	m_pMaterials.erase(it);
}

PhysicsMaterial2D* divengine::MaterialManager::GetMaterial( int id) const
{
	if (id == -1)
		return nullptr;

	const auto it = m_pMaterials.find(id);
	if (it == m_pMaterials.end())
	{
		Debug::LogWarning("MaterialManager::GetMaterial: Material with id ", id, "not found");
		return nullptr;
	}
	return it->second;
}
