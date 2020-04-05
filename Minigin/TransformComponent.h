#pragma once
#include "BaseComponent.h"

namespace dae
{
	class TransformComponent : public BaseComponent
	{
	public:
		TransformComponent(const Vector3& position);
		virtual ~TransformComponent() = default;
		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) = delete;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) = delete;

		void SetPosition(const Vector3 & pos);
		void SetPosition(float x, float y, float z);
		Vector3 GetPosition() const;

	protected:
		void Update(float MsPerUpdate) override;
		void Render() override;

	private:
		Vector3 m_Position;
	};
}