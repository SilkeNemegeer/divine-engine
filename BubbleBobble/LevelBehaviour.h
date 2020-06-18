#pragma once
#include "BaseComponent.h"

class LevelBehaviour : public divengine::BaseComponent
{
public:
	LevelBehaviour() = default;
	virtual void Update() override {};
	virtual void Render() override {};
	virtual void Initialize() override {};
	virtual void Start() override {};

private:
};

