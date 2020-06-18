#include "MiniginPCH.h"
#include "Structs.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ColliderComponent.h"
#include "GameObject.h"
#include <algorithm>


bool divengine::HorizontalRaycast(const glm::vec2& origin, float rayLength, const glm::vec2& dir, HitInfo& hitInfo)
{
	//Check if any of the objects are colliding with the ray, return the closest object in hitinfo
	glm::vec2 endRay = origin + dir * rayLength;

	//create small box around the ray
	Rectf rayRect;
	rayRect.bottomLeft.x = std::min(origin.x, endRay.x);
	rayRect.bottomLeft.y = std::min(origin.y, endRay.y);

	rayRect.width = std::max(origin.x, endRay.x) - rayRect.bottomLeft.x;
	rayRect.height = std::max(origin.y, endRay.y) - rayRect.bottomLeft.y;

	auto colliders = SceneManager::GetInstance().GetCurrentScene()->GetColliders();
	//Find nearest collider
	float smallestDist = FLT_MAX;
	bool foundMatch = false;
	for (size_t i = 0; i < colliders.size(); i++)
	{
		if (colliders[i]->IsColliding(rayRect)) 
		{
			foundMatch = true;
			GameObject* pCollider = colliders[i]->GetGameObject();
			//Find the distance from the origin of the ray and the center of the rect
			float distance = Distance(origin, pCollider->GetPos());
			if (distance < smallestDist)
			{
				hitInfo.pCollider = colliders[i];
				hitInfo.distance = distance;
				smallestDist = distance;
			}
		}
	}

	return foundMatch;
}

//TODO: create IsColliding for lines for all components