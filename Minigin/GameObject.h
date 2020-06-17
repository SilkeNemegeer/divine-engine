#pragma once
#include "Structs.h"
#include <functional>
#include <string>
#include <vector>
#include "BinaryReader.h"
#include "BinaryWriter.h"
#include "TransformComponent.h"

namespace divengine
{
	class BaseComponent;
	//class TransformComponent;

	//class Texture2D;
	class GameObject final
	{
	public:
		enum class TriggerFlag
		{
			enter,
			leave,
			stay
		};

		typedef std::function<void(GameObject * trigger, GameObject * other, TriggerFlag action)> TriggerCallback;

		virtual void Update();
		virtual void Render() const;
		virtual void Initialize();

		void SetPosition(float x, float y, float z = 0.f);
		void SetPosition(const Vector3& newPos);
		Vector3 GetPosition() const;
		glm::vec2 GetPos() const;
		void SetPos(const glm::vec2& pos);
		void SetPos(float x, float y);
		float GetScale() const;
		TransformComponent* GetTransform() const;
	
		void SetTag(const std::string& tag) { m_Tag = tag; };
		const std::string& GetTag() const { return m_Tag; };

		void SetActive(bool isActive) { m_IsActive = isActive; };
		bool IsActive() const { return m_IsActive; };


		void AddComponent(BaseComponent* pComponent, bool initOnCreation = false);
		void RemoveComponent(BaseComponent* pComponent);

		const std::vector<BaseComponent*> &Components() const { return m_pComponents; };

		//void OnTrigger(GameObject* trigger, GameObject* other, TriggerFlag flag) {};
		//void OnCollision(GameObject* collider, GameObject* other, TriggerFlag flag) {};

		void SetTriggerCallback(TriggerCallback callback); //Make ontrigger enter, oncollision enter , ... (also for the components, call these functions for the components)

		virtual void OnCollisionEnter(GameObject* collider);
		virtual void OnCollisionStay(GameObject* collider);
		virtual void OnCollisionExit(GameObject* collider);

		virtual void OnTriggerEnter(GameObject* trigger);
		virtual void OnTriggerStay(GameObject* trigger);
		virtual void OnTriggerExit(GameObject* trigger);

		void Load(BinaryReader& reader);
		void Save(BinaryWriter& writer);

		//TODO: make oncollision callback


		GameObject(const Vector3& position = Vector3(), float scale = 1);
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
		TriggerCallback m_TriggerCallback;
		TransformComponent* m_Transform; //a lot of GameObjects have a position, having it here will be more efficient
		std::string m_Tag;
		bool m_IsActive;
		bool m_IsInitialized;
	};
}
