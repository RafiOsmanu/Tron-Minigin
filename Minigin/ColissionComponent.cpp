#include "ColissionComponent.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Commands.h"

namespace dae
{
	void ColissionComponent::Update()
	{
		if (!m_pOwner.lock().get()->IsMoving() )
		{
			for (Cube& cube : m_MapCubes)
			{
				if(cube.isActive)
					continue;

				if (IsColliding(m_pOwner.lock().get()->GetLocalPosition(), cube))
				{
					cube.texture = ResourceManager::GetInstance().LoadTexture("ActiveCube.png");
					cube.isActive = true;
				}
				else if(IsNotColliding())
				{
					m_IsPlayerDead = true;
				}
			}
		}
	}

	void ColissionComponent::Render()
	{
		//nothing to render
		//SDL_Rect rect{ static_cast<int>(m_pOwner.lock().get()->GetLocalPosition().x + 5), static_cast<int>(m_pOwner.lock().get()->GetLocalPosition().y + 10), static_cast<int>(10), static_cast<int>(10)};
		//Renderer::GetInstance().DrawRect(rect);
	}

	bool ColissionComponent::IsColliding(glm::vec2 playerPos, Cube mapCube)
	{
		//collision detection

		auto cubeRight = mapCube.position.x + mapCube.size;
		auto cubeBottom = mapCube.position.y + mapCube.size / 2;

		if (playerPos.x + 5 < mapCube.position.x || playerPos.x > cubeRight)
			return false;

		if (playerPos.y + 10 < mapCube.position.y || playerPos.y > cubeBottom)
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
