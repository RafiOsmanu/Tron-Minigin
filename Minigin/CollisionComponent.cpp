#include "CollisionComponent.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Commands.h"

namespace dae
{
	void CollisionComponent::Update()
	{
		if (m_IsDead) return;

		for (Cube& cube : m_MapCubes)
		{
			
			if (IsColliding(m_FuturePos, cube) && (cube.cubeType == dae::MapTerrain::wall || cube.cubeType == dae::MapTerrain::voidTile))
			{
				m_IsColliding = true;
				m_IsNotColliding = false;
				break;
			}
			else if (IsColliding(m_FuturePos, cube) && (cube.cubeType == dae::MapTerrain::teleport))
			{
				auto randIndex = rand() % m_PathCubes.size();
				m_pOwner.lock()->SetLocalPosition(m_PathCubes.at(randIndex).position);
			}
			
			m_IsColliding = false;
			m_IsNotColliding = true;
		
		}
		
	}

	void CollisionComponent::Render()
	{
		if (m_IsDead) return;
		//nothing to render
		SDL_Rect rect{ static_cast<int>(m_pOwner.lock().get()->GetLocalPosition().x), static_cast<int>(m_pOwner.lock().get()->GetLocalPosition().y), static_cast<int>(7), static_cast<int>(7) };
		Renderer::GetInstance().DrawRect(rect);
	}

	bool CollisionComponent::IsColliding(glm::vec2 playerPos, Cube mapCube)
	{
		// Calculate the half extents of the player's collision box
		float playerHalfWidth = 3.5f;  // Half of player's collision box width (15 / 2)
		float playerHalfHeight = 3.5f; // Half of player's collision box height (15 / 2)

		// Calculate the minimum and maximum extents of the player's collision box
		float playerMinX = playerPos.x - playerHalfWidth;
		float playerMaxX = playerPos.x + playerHalfWidth;
		float playerMinY = playerPos.y - playerHalfHeight;
		float playerMaxY = playerPos.y + playerHalfHeight;

		// Calculate the minimum and maximum extents of the map cube
		float cubeMinX = mapCube.position.x;
		float cubeMaxX = mapCube.position.x + mapCube.size;
		float cubeMinY = mapCube.position.y;
		float cubeMaxY = mapCube.position.y + mapCube.size;

		// Perform AABB collision check
		if (playerMaxX < cubeMinX || playerMinX > cubeMaxX || playerMaxY < cubeMinY || playerMinY > cubeMaxY)
			return false;

		return true;
	}

	bool CollisionComponent::IsNotColliding()
	{
		if (!m_pOwner.lock().get()->IsMoving())
		{
			for (Cube& cube : m_MapCubes)
			{
				if (IsColliding(m_pOwner.lock().get()->GetLocalPosition(), cube))
				{
					return false;
				}
			}
		}
		return true;
	}
}
