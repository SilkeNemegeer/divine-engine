#pragma once
#include "Structs.h"
#include "BinaryReader.h"
#include "BinaryWriter.h"
namespace divengine
{
	class GameObject;

	enum class ComponentType : unsigned int
	{
		collidercomponent
		,boxcollider
		,circlecollider
		,platformcollider
		,fpscomponent
		,rendercomponent
		,rigidbodycomponent
		,textcomponent
		,transformcomponent
		,animator
		,unknown
		,TYPECOUNT
	};

	class BaseComponent
	{
		friend class GameObject;

	public:
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) noexcept = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) noexcept = delete;
		BaseComponent();
		virtual ~BaseComponent() = default;

		//virtual void Load(std::istream& ) {}; //TODO: make this abstract so every component has this
		//virtual void Save(std::ostream& ) {};
		virtual void OnCollisionEnter(GameObject* ) {};
		virtual void OnCollisionStay(GameObject* ) {};
		virtual void OnCollisionExit(GameObject* ) {};

		virtual void OnTriggerEnter(GameObject* ) {};
		virtual void OnTriggerStay(GameObject* ) {};
		virtual void OnTriggerExit(GameObject* ) {};
		
		virtual void Load(BinaryReader& ) {}; //TODO: make this abstract so every component has this
		virtual void Save(BinaryWriter& ) {};
		int Type() const { return m_TypeId; };

		GameObject* GetGameObject() const;
	protected:
		virtual void Update() = 0;
		virtual void Initialize() = 0;
		virtual void PostInitialize() {};
		virtual void Render() = 0;
		virtual void Start() {}; //when scene is activated, this will be called

		GameObject* m_pGameObject;
		unsigned int m_TypeId;

	};
}
