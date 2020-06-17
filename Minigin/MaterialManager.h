#pragma once
#include "Singleton.h"
#include "PhysicsMaterial2D.h"
#include <map>

namespace divengine
{
	class MaterialManager final: public Singleton<MaterialManager>
	{
	public:

		MaterialManager(const MaterialManager& other) = delete;
		MaterialManager(MaterialManager&& other) noexcept = delete;
		MaterialManager& operator=(const MaterialManager& other) = delete;
		MaterialManager& operator=(MaterialManager&& other) noexcept = delete;
		MaterialManager();
		~MaterialManager();

		void AddMaterial(PhysicsMaterial2D* pMaterial, int id);
		void RemoveMaterial(int id);
		PhysicsMaterial2D* GetMaterial(int id) const;

	private:
		std::map<int, PhysicsMaterial2D*> m_pMaterials;
	};
}