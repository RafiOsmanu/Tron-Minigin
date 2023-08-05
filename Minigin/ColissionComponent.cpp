#include "ColissionComponent.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Commands.h"

namespace dae
{
	void ColissionComponent::Update()
	{
		
		for (Cube& cube : m_MapCubes)
		{
			
			if (IsColliding(m_FuturePos, cube) && cube.cubeType == dae::MapTerrain::voidTile)
			{
				m_IsColliding = true;
				m_IsNotColliding = false;
				break;
			}
			
			m_IsColliding = false;
			m_IsNotColliding = true;
		
		}
		
	}

	void ColissionComponent::Render()
	{
		//nothing to render
		SDL_Rect rect{ static_cast<int>(m_pOwner.lock().get()->GetLocalPosition().x), static_cast<int>(m_pOwner.lock().get()->GetLocalPosition().y), static_cast<int>(15), static_cast<int>(15) };
		Renderer::GetInstance().DrawRect(rect);
	}

	bool ColissionComponent::IsColliding(glm::vec2 playerPos, Cube mapCube)
	{
		//collision detection

		auto cubeRight = mapCube.position.x + mapCube.size;
		auto cubeBottom = mapCube.position.y + mapCube.size;

		if (playerPos.x < mapCube.position.x || playerPos.x > cubeRight)
			return false;

		if (playerPos.y < mapCube.position.y || playerPos.y > cubeBottom)
			return false;

		return true;
	}

	bool ColissionComponent::IsNotColliding()
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
