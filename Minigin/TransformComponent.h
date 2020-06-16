#pragma once
#include "BaseComponent.h"

namespace divengine
{
	class TransformComponent : public BaseComponent
	{
	public:
		TransformComponent(const Vector3& position, float scale = 1);
		TransformComponent(const glm::vec2& pos = glm::vec2(), float scale = 1);
		virtual ~TransformComponent() = default;
		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) = delete;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) = delete;

		void SetPosition(const Vector3 & pos);
		void SetPosition(float x, float y, float z);
		Vector3 GetPosition() const;
		void SetScale(float newScale);
		float GetScale() const;
		//virtual void Load(std::istream& istream) override;
		//virtual void Save(std::ostream& istream) override;

		virtual void Load(BinaryReader& reader) override;
		virtual void Save(BinaryWriter& writer) override;

	protected:
		void Update() override;
		void Render() override;
		void Initialize() override;

	private:
		float m_Scale;
		Vector3 m_Position;
	};
}