#pragma once
#include "BaseComponent.h"
#include <vector>
#include "AnimationsEnum.h"
//Controls enemies
class EnemyBehaviour;
class EnemyState;

namespace divengine
{
	class RigidbodyComponent;
	class GameObject;
	class Animator;
}

//
class AIController : public divengine::BaseComponent
{
public:
	AIController();
	~AIController();

	AIController(const AIController& other) = delete;
	AIController(AIController&& other) = delete;
	AIController& operator=(const AIController& other) = delete;
	AIController& operator=(AIController&& other) = delete;

	void LinkEnemy(EnemyBehaviour* pEnemy);

	virtual void Load(divengine::BinaryReader& reader) override;
	virtual void Save(divengine::BinaryWriter& writer) override;

protected:
	virtual void Update() override;
	virtual void Render() override {};
	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void Start() override;
private:

	void ChangeState(EnemyState* pNewState);
	bool m_IsLookingLeft;
	divengine::RigidbodyComponent* m_pRigidbody;
	EnemyBehaviour* m_pEnemyBehaviour;
	divengine::Animator* m_pAnimator;
	std::vector<divengine::GameObject*> m_pPlayers;
	EnemyState* m_pCurrentState;
};

