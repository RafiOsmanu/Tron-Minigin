#pragma once
#include<iostream>
#include <cstdlib>
#include <map>

#include "Gamepad.h"
#include "Command.h"

#include "Singleton.h"


namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();

	};

}
