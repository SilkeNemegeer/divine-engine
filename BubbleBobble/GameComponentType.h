#pragma once

enum class GameComponentType : unsigned int
{
	playercontroller = unsigned int(divengine::ComponentType::TYPECOUNT),
	button,
	health,
	menucontroller,
	itembehaviour,
	hud,
	zenchanbehaviour,
	maitabehaviour,
	aicontroller
};