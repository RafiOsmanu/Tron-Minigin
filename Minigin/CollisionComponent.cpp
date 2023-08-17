#include "CollisionComponent.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Commands.h"
#include "DamageComponent.h"
#include "EnemyAiComponent.h"
#include "ServiceLocator.h"

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
				std::vector<Cube> pathCubes;
				for (auto& pathCube : m_MapCubes)	
				{
					if (pathCube.cubeType == dae::MapTerrain::path)
						pathCubes.push_back(pathCube);
				}
				auto randIndex = rand() % pathCubes.size();
				Cube teleportPosCube = pathCubes.at(randIndex);
				auto halfsize = teleportPosCube.size / 2.f;

				m_pOwner.lock()->SetLocalPosition({ teleportPosCube.position.x + halfsize , teleportPosCube.position.y + halfsize });

				//play teleport sound
				Engine::ServiceLocator::GetAudioSystem().Play((Engine::SoundId)Engine::Sound::teleport, 3.f);
				
			}
			
			m_IsColliding = false;
			m_IsNotColliding = true;
		
		}

		if (!m_pOwner.lock()->GetComponent<EnemyAiComponent>()) return;
		if (m_pOwner.lock()->GetComponent<EnemyAiComponent>()->GetEnemyType() != dae::EnemyType::recognizer) return;

		for (auto& player : m_PlayersToCollideWith)
		{
			if (IsCollidingWithPlayer(m_pOwner.lock()->GetLocalPosition(), player.lock()->GetLocalPosition()))
			{
				player.lock()->GetComponent<DamageComponent>()->KillOwner();
			}	
		}
	}

	void CollisionComponent::Render()
	{
		if (m_IsDead) return;
		//nothing to render
		/*SDL_Rect rect{ static_cast<int>(m_pOwner.lock().get()->GetLocalPosition().x), static_cast<int>(m_pOwner.lock().get()->GetLocalPosition().y), static_cast<int>(7), static_cast<int>(7) };
		Renderer::GetInstance().DrawRect(rect);*/
	}

	bool CollisionComponent::IsColliding(glm::vec2 playerPos, Cube& mapCube)
	{
		// Calculate the half extents of the player's collision box
		float playerHalfWidth = m_CollisionBoxSize / 2.f;
		float playerHalfHeight = m_CollisionBoxSize / 2.f;

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

	bool CollisionComponent::IsCollidingWithPlayer(glm::vec2 playerPos, glm::vec2 playerPos2)
	{
		// Calculate the half extents of the player's collision box
		float playerHalfWidth = m_CollisionBoxSize;  
		float playerHalfHeight = m_CollisionBoxSize; 

		// Calculate the minimum and maximum extents of the player's collision box
		float playerMinX = playerPos.x - playerHalfWidth;
		float playerMaxX = playerPos.x + playerHalfWidth;
		float playerMinY = playerPos.y - playerHalfHeight;
		float playerMaxY = playerPos.y + playerHalfHeight;

		// Calculate the minimum and maximum extents of the player's collision box
		float playerMinX2 = playerPos2.x - playerHalfWidth;
		float playerMaxX2 = playerPos2.x + playerHalfWidth;
		float playerMinY2 = playerPos2.y - playerHalfHeight;
		float playerMaxY2 = playerPos2.y + playerHalfHeight;

		// Perform AABB collision check
		if (playerMaxX < playerMinX2 || playerMinX > playerMaxX2 || playerMaxY < playerMinY2 || playerMinY > playerMaxY2)
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
