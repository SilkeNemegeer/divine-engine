#pragma once
#include "BaseComponent.h"

namespace divengine
{
	class ControllerComponent : public BaseComponent
	{
	public:
		void Jump();


	private:
		int m_PlayerId;
	};
}
