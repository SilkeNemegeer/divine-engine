#pragma once
struct PhysicsMaterial2D
{
	PhysicsMaterial2D(float friction = 0.f, float bounciness = 0.f) :Friction{ friction }, Bounciness{ bounciness } {}
	float Friction; //coefficient of friction
	float Bounciness; //degree to which collisions rebound from surface, a value of 0 indicates no bounce, 1 indicates perfect bounce with no loss of energy
};