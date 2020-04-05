#pragma once
#include "SceneObject.h"
#include "Structs.h"
namespace dae
{
	class BaseComponent;
	class TransformComponent;

	//class Texture2D;
	class GameObject final
	{
	public:
		void Update(float MsPerUpdate);
		void Render() const;

		void SetPosition(float x, float y, float z = 0.f);
		void SetPosition(const Vector3& newPos);
		Vector3 GetPosition() const;
	
		void AddComponent(BaseComponent* pComponent);
		void RemoveComponent(BaseComponent* pComponent);

		GameObject(const Vector3& position = Vector3());
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

#pragma region Template functions
		//Template functions
		template<class T>
		T* GetComponent()
		{
			//Find first component of type T
			const auto& type = typeid(T);
			for (BaseComponent* pComponent : m_pComponents)
			{
				if (pComponent && (typeid(*pComponent) == type))
				{
					return static_cast<T*>(pComponent);
				}
			}
			return nullptr;
		}

		template<class T>
		std::vector<T*> GetComponents()
		{
			const auto& type = typeid(T);
			std::vector<T*> components;
			//Get all components of type T
			for (BaseComponent* pComponent : m_pComponents)
			{
				if (pComponent && (typeid(*pComponent) == type))
				{
					components.push_back(static_cast<T*>(pComponent));
				}
			}
			return components;
		}
#pragma endregion

	private:
		std::vector<BaseComponent*> m_pComponents;

		TransformComponent* m_Transform; //a lot of GameObjects have a position, having it here will be more efficient
	};
}
