#pragma once
#include "BaseComponent.h"

namespace divengine
{
	class TransformComponent;
	class RigidbodyComponent;
	class GameObject;
}

class BubbleBehaviour : public divengine::BaseComponent
{
public:
	BubbleBehaviour();
	~BubbleBehaviour() {};

	BubbleBehaviour(const BubbleBehaviour& other) = delete;
	BubbleBehaviour(BubbleBehaviour&& other) = delete;
	BubbleBehaviour& operator=(const BubbleBehaviour& other) = delete;
	BubbleBehaviour& operator=(BubbleBehaviour&& other) = delete;

	virtual void Update() override;
	virtual void Render() override {};
	virtual void Initialize() override;

	virtual void OnTriggerEnter(divengine::GameObject* trigger) override;

	//Here check collisions with enemies

private:

	float m_MaxLifeTime;
	float m_CurrentLifeTimePassed;
	divengine::TransformComponent* m_pTransform;
	divengine::RigidbodyComponent* m_pRigidbody;
	float m_UpwardsForce;
};

