#include "MiniginPCH.h"
#include "BoxColliderComponent.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "SDL.h"
#include "Scene.h"
#include "DebugRenderer.h"
#include "TransformComponent.h"
#include "Renderer.h"
#include "RigidbodyComponent.h"
//
//divengine::BoxColliderComponent::BoxColliderComponent(const glm::vec2& dimensions, const glm::vec2& offset, bool isTrigger, PhysicsMaterial2D* pMaterial)
//	:m_Rect{glm::vec2(), dimensions.x, dimensions.y }
//	, ColliderComponent::ColliderComponent(isTrigger, pMaterial)
//	,m_Offset{offset}
//{
//	m_Type = ColliderComponent::ColliderType::rect;
//	m_TypeId = unsigned int(ComponentType::boxcollider);
//}

divengine::BoxColliderComponent::BoxColliderComponent(const glm::vec2& dimensions, const glm::vec2& offset, bool isTrigger, int materialId)
	:m_Rect{ glm::vec2(), dimensions.x, dimensions.y }
	, ColliderComponent::ColliderComponent(isTrigger, materialId)
	, m_Offset{ offset }
{
	m_Type = ColliderComponent::ColliderType::rect;
	m_TypeId = unsigned int(ComponentType::boxcollider);
}

bool divengine::BoxColliderComponent::IsColliding(const Rectf& rect, bool isPlatform) const
{
	if (isPlatform)
	{
		if (m_pRigidbody->GetVelocity().y < 0.f)
			return false;
	}
	//Check x collisions
	if (m_Rect.bottomLeft.x >= rect.bottomLeft.x + rect.width || m_Rect.bottomLeft.x + m_Rect.width < rect.bottomLeft.x)
		return false;

	//Check y collisions
	if (m_Rect.bottomLeft.y >= rect.bottomLeft.y + rect.height || m_Rect.bottomLeft.y + m_Rect.height < rect.bottomLeft.y)
		return false;

	return true;
}

bool divengine::BoxColliderComponent::IsColliding(const Circlef& circle) const
{
	//Calc distance between two center of the shapes
	float halfWidthRect = m_Rect.width / 2.f;
	float halfHeightRect = m_Rect.height / 2.f;
	glm::vec2 dist{};
	dist.x = abs(circle.center.x - (m_Rect.bottomLeft.x + halfWidthRect));
	dist.y = abs(circle.center.y - (m_Rect.bottomLeft.y + halfHeightRect));

	//Compare all sides of the rect with the distance between the two centers
	if (dist.x > (halfWidthRect + circle.radius))
		return false;

	if (dist.y > (halfHeightRect + circle.radius))
		return false;

	if (dist.x <= halfWidthRect)
		return true;

	if (dist.y <= halfHeightRect)
		return true;

	float cornerDist = Square(dist.x - halfWidthRect) + Square(dist.y - halfHeightRect);
	return cornerDist <= Square(circle.radius);
}

glm::vec2 divengine::BoxColliderComponent::ResolveCollision(const Rectf& rect, float restitution)
{
	auto newPosition = m_pTransform->GetPosition();
	auto newVelocity = m_pRigidbody->GetVelocity();

	//Find centers
	glm::vec2 center = glm::vec2(m_Rect.bottomLeft.x + m_Rect.width / 2.f, m_Rect.bottomLeft.y + m_Rect.height / 2.f);
	glm::vec2 otherCenter = glm::vec2(rect.bottomLeft.x + rect.width / 2.f, rect.bottomLeft.y + rect.height/ 2.f);

	//Calc absolute changes in x and y
	glm::vec2 deltaCenterOffset{};
	deltaCenterOffset.x = (otherCenter.x - center.x) / (rect.width/2.f);
	deltaCenterOffset.y = (otherCenter.y -center.y )  / (rect.height/2.f);

	float absX = abs(deltaCenterOffset.x);
	float absY = abs(deltaCenterOffset.y);

	//According to if x side or y side penetrates more, it will change the vel
	//if the distance between the normalized x and y position is less than small treshold -> object is approaching from corner
	if (abs(absX - absY) < 0.1f) //CORNERS
	{
		//Calc X pos
		//if player is approaching from positive x
		if (deltaCenterOffset.x < 0)
		{
			//Set this x pos to right side of other rect
			newPosition.x = rect.bottomLeft.x + rect.width;
		}
		else //player is approaching from negative x
		{
			newPosition.x = rect.bottomLeft.x - m_Rect.width;
		}

		//Calc Y pos
		if (deltaCenterOffset.y < 0) //this is approaching rect with positive y
		{
			//set y pos to the bottom
			newPosition.y = rect.bottomLeft.y + rect.height;
		}
		else //this is approaching from negative y
		{
			newPosition.y = rect.bottomLeft.y - m_Rect.height;
		}

		//randomly reflect velocity towards an x or y direction
		//....
		if (rand() % 2)
		{
			newVelocity.x = -newVelocity.x * restitution;

			if (abs(newVelocity.x) < 0.004f)
				newVelocity.x = 0.f;
		}
		else
		{
			newVelocity.y = -newVelocity.y * restitution;
			if (abs(newVelocity.y) < 0.004f)
				newVelocity.y = 0;
		}

	}
	else if(absX > absY) //SIDES //other rect is approaching from sides
	{
		//Only have to set x position differently
		if (deltaCenterOffset.x < 0) //this is approaching from positive x -> should be on right
		{
			newPosition.x = rect.bottomLeft.x + rect.width;//- m_Rect.width;
		}
		else //approaching from negative x -> this should be on the left of the other rect
		{
			newPosition.x = rect.bottomLeft.x - m_Rect.width;// -m_Rect.width;// +rect.width;
		}

		//velocity
		newVelocity.x = -newVelocity.x * restitution;

		if (abs(newVelocity.x) < 0.004f)
		{
			newVelocity.x = 0.f;
		}

	}
	else //TOP OR BOTTOM //collision is coming from the top or bottom
	{
		if (deltaCenterOffset.y < 0) //approaching from positive y -> this should underneath other rect
		{
			newPosition.y = rect.bottomLeft.y + rect.height;// +m_Rect.height;
		}
		else //if this should be above the other rect -> put it back on tops
		{

			newPosition.y = rect.bottomLeft.y - m_Rect.height; // - rect.height + m_Rect.height;
		}

		//Velocity
		newVelocity.y = -newVelocity.y * restitution;
		if (abs(newVelocity.y) < 0.004f)
		{
			newVelocity.y = 0;
		}
	}

	//m_pRigidbody->SetVelocity(newVelocity);
	m_pTransform->SetPosition(newPosition);

	return glm::vec2(absX, absY);
}

glm::vec2 divengine::BoxColliderComponent::ResolveCollision(const Circlef& , float )
{
	return glm::vec2();
}

void divengine::BoxColliderComponent::Load(divengine::BinaryReader& reader)
{
	//Rect & offset
	reader.Read(m_Rect);
	reader.Read(m_Offset);
}

void divengine::BoxColliderComponent::Save(divengine::BinaryWriter& writer)
{
	writer.Write(m_Rect);
	writer.Write(m_Offset);
}

void divengine::BoxColliderComponent::Update()
{
	//Set collider position equal to position of object
	//m_Collider.x = 
	auto pos = m_pGameObject->GetPosition();
	m_Rect.bottomLeft.x = pos.x + m_Offset.x;
	m_Rect.bottomLeft.y = pos.y + m_Offset.y;
}

void divengine::BoxColliderComponent::Initialize()
{
	ColliderComponent::Initialize();
	auto pos = m_pGameObject->GetPosition();
	m_Rect.bottomLeft.x = pos.x + m_Offset.x;
	m_Rect.bottomLeft.y = pos.y + m_Offset.y;
}

void divengine::BoxColliderComponent::Render()
{
	DebugRenderer::DrawRect(m_Rect, 255, 0, 0, 255);
}
