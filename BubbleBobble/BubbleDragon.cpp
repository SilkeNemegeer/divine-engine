#include "BubbleDragon.h"

void BubbleDragon::HandleInput(InputComponent* input)
{
	BubbleDragonState* newState = m_pState->HandleInput(this, input);
	if (newState != nullptr)
	{
		delete m_pState;
		m_pState = newState;
	}
}

void BubbleDragon::Update()
{

}

void BubbleDragon::Initialize()
{
	SetTag("BubbleDragon");
}

void BubbleDragon::Jump()
{

}
