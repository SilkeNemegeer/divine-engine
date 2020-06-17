#pragma once
#include "BaseComponent.h"
namespace divengine
{
	class GameObject;
}
class ItemBehaviour : public divengine::BaseComponent
{
public:
	ItemBehaviour(float score);
	~ItemBehaviour() {};

	ItemBehaviour(const ItemBehaviour& other) = delete;
	ItemBehaviour(ItemBehaviour&& other) = delete;
	ItemBehaviour& operator=(const ItemBehaviour& other) = delete;
	ItemBehaviour& operator=(ItemBehaviour&& other) = delete;

	virtual void OnTriggerEnter(divengine::GameObject* pCollider);

protected:
	virtual void Update() override;
	virtual void Render() override {};
	virtual void Initialize() override;

private:
	float m_Score;
};

