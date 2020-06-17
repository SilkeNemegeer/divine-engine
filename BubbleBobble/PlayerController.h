#pragma once
#include "BaseComponent.h"

namespace divengine
{
	class ColliderComponent;
	class RigidbodyComponent;
	class Animator;
}

class PlayerController : public divengine::BaseComponent
{
public:
	//enum class State : int
	//{
	//	walkLeft, walkRight, idle, attackLeft, attackRight
	//};

	enum class State
	{
		walkLeft, walkRight, idle, attack, dead
	};

	PlayerController(int id = 0);
	~PlayerController();

	PlayerController(const PlayerController& other) = delete;
	PlayerController(PlayerController&& other) = delete;
	PlayerController& operator=(const PlayerController& other) = delete;
	PlayerController& operator=(PlayerController&& other) = delete;

	virtual void Update() override;
	virtual void Render() override {};
	virtual void Initialize() override;

	void MoveLeft();
	void MoveRight();
	void Jump();
	void Attack();

	void SetAnimation(State anim);

	int GetPlayerId() const { return m_PlayerId; };

private:
	void ChangeState(State newState);
	int m_PlayerId;
	bool m_IsFacingLeft;
	State m_CurrentState;

	//Attack params
	float m_MaxAttackTime;
	float m_CurrentAttackTime;

	void FireBubble();
	float m_FireBubbleForce;

	divengine::RigidbodyComponent* m_pRigidbody;
	divengine::Animator* m_pAnimator;
};

