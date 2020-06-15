#pragma once
#include "Character.h"
#include "BubbleDragonState.h"
#include "BaseComponent.h"
using namespace divengine;
class BubbleDragon : public BaseComponent//: public Character//protagonist /player
{
	//Has 4 lives
	//
	//has controller component (with playerid (so that input updates for correct dragon), calls move & interact functions,handles input player, ...)
	//has collision
	//has rigidbody
	//has health component (made in game not engine)
public:
	virtual void Update() override;
	virtual void Initialize() override;
	virtual void Render() override {};
	void Jump();


protected:


private:
	BubbleDragonState* m_pState;
	//can jump on top of players, walk, fire bubble from mouth, 
};

