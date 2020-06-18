#pragma once
#include "BaseComponent.h"
#include "AnimationsEnum.h"

namespace divengine
{
	class ColliderComponent;
	class RigidbodyComponent;
	class Animator;
}

class Health;
class PlayerController : public divengine::BaseComponent
{
public:
	enum class PlayerType
	{
		bub, bob
	};

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
	virtual void Start() override;

	void MoveLeft();
	void MoveRight();
	void Jump();
	void Attack();

	void AddToScore(float points) { m_Score += points; };
	float GetScore() const { return m_Score; };
	void ResetScore() { m_Score = 0.f; };

	void SetAnimation(State anim);

	int GetPlayerId() const { return m_PlayerId; };

private:
	void ChangeState(State newState);
	void Die();
	int m_PlayerId;
	bool m_IsFacingLeft;
	State m_CurrentState;

	//Health params
	Health* m_pHealth;
	int m_MaxLives;
	float m_TotalRespawnTime;
	float m_CurrentDeadTime;

	//Attack params
	float m_MaxAttackTime;
	float m_CurrentAttackTime;

	void FireBubble();
	float m_FireBubbleForce;

	//Score
	float m_Score;

	//Components
	divengine::RigidbodyComponent* m_pRigidbody;
	divengine::Animator* m_pAnimator;
};

