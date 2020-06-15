#pragma once
#include "BaseComponent.h"

namespace divengine
{
	class ColliderComponent;
	class RigidbodyComponent;
}

class PlayerController : public divengine::BaseComponent
{
public:
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

	int GetPlayerId() const { return m_PlayerId; };

private:
	int m_PlayerId;
	divengine::RigidbodyComponent* m_pRigidbody;

};

