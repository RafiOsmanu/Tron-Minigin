#pragma once
#include <glm/glm.hpp>
#include "Texture2D.h"
#include <memory>

namespace dae
{
	enum EventType {
		PlayerDied,
		PlayerDamage,
		PlayerScoreAdd
	};

	enum TankInput
	{
		Left,
		Right, 
		Up,
		Down,
	};

	enum TourretInput
	{
		TourretLeft,
		TourretRight,
		TourretUp,
		TourretDown,
	};

	struct Cube
	{
		glm::vec2 position;  // The position of the cube in world space
		float size;          // The size of the cube
		glm::vec3 color;     // The color of the cube
		std::shared_ptr<Texture2D> texture;
		bool isActive = false;
	};
}

