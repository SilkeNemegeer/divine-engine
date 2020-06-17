#pragma once
#include "BaseComponent.h"

//Makes enemies wander & follow players (gameobjects with tags "player")
namespace divengine
{
	class ColliderComponent;
	class RigidbodyComponent;
}

//
class AIController : public divengine::BaseComponent
{
public:
	AIController();
	~AIController() {};

	AIController(const AIController& other) = delete;
	AIController(AIController&& other) = delete;
	AIController& operator=(const AIController& other) = delete;
	AIController& operator=(AIController&& other) = delete;

protected:
	virtual void Update() override;
	virtual void Render() override {};
	virtual void Initialize() override;

private:
	divengine::RigidbodyComponent* m_pRigidbody;
	divengine::ColliderComponent* m_pCollider;
};

