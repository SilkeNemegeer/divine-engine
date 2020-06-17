#pragma once
namespace divengine
{
	class RigidbodyComponent;
	class Animator;


}
class PlayerController;

	class PlayerState
	{
	public:
		virtual ~PlayerState() {};
		virtual PlayerState* Update(PlayerController* player) = 0;
		virtual void Enter(PlayerController* ) {};
		virtual void Exit(PlayerController* ) {};

	private:
	};

	//class MoveState : public PlayerState
	//{
	//public:
	//	virtual PlayerState* Update(PlayerController* player) override;
	//	virtual void Enter(PlayerController* player) override;

	//};

	////class AttackState : public PlayerState
	////{
	////public:
	////virtual PlayerState* Update(PlayerController* player) override;
	////virtual void Enter(PlayerController* player) override;
	////private:
	////};

	////class DeadState : public PlayerState
	////{
	////public:
	///*virtual PlayerState* Update(PlayerController* player) override;
	//virtual void Enter(PlayerController* player) override;*/

	////private:

	////};

	//class IdleState : public PlayerState
	//{
	//public:
	//	virtual PlayerState* Update(PlayerController* player) override;
	//	virtual void Enter(PlayerController* player) override;
	//private:

	//};