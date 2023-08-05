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
		Left = 180,
		Right = 0, 
		Up = 270,
		Down = 90,
	};

	enum TourretInput
	{
		TourretLeft = 180,
		TourretLeftUp = 225,
		TourretLeftDown = 135,
		TourretRight = 0,
		TourretRightUp = 315,
		TourretRightDown = 45,
		TourretUp = 270,
		TourretDown = 90,
		TourretShoot = 1
	};

	enum InputState
	{
		SingleInput, WaitForDoubleInput
	};

	enum MapTerrain
	{
		wall, teleport, voidTile, path 
	};

	struct Cube
	{
		glm::vec2 position;  // The position of the cube in world space
		float size;          // The size of the cube
		glm::vec3 color;     // The color of the cube
		std::shared_ptr<Texture2D> texture;
		bool isActive = false;
		MapTerrain cubeType;



	};
}

