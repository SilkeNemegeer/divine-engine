#pragma once
#include "BaseComponent.h"
namespace divengine
{
	class InputComponent : public divengine::BaseComponent
	{
	public:
		virtual ~InputComponent() {};
		virtual void Update() override = 0; //can be written differently per gameObject, update the input here (add forces to rigidbody, ...)
		virtual void Initialize() override = 0;
		virtual void Render() override = 0;
	};
}