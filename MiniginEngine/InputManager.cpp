#include <SDL.h>
#include "InputManager.h"
#include "imgui_impl_sdl2.h"
#include "Input.h"
using namespace dae;

bool dae::InputManager::ProcessInput()
{

	SDL_Event e;

	auto controllers = Input::GetInstance().GetControllers();
	auto ControllerCommands = Input::GetInstance().GetControllerCommands();
	auto KeyboardCommands = Input::GetInstance().GetKeyboardCommands();
	auto keyboard = Input::GetInstance().GetKeyboard();
	auto DoubleInputCommands = Input::GetInstance().GetDoubleInputCommands();

	for (const auto& controller : controllers)
	{
		controller->Update();
	}

	for (const auto& comm : ControllerCommands)
	{
		//get controller index from key
		auto& controller = controllers[comm.first.first];

		//get button from key
		auto button = comm.first.second;

		//if the right button is down on controller execute command
		if (controller->IsPressed(button))
		{
			comm.second->Execute();
		}
	}
	
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
		// procces event for imgui
		ImGui_ImplSDL2_ProcessEvent(&e);
		
	}


	if(keyboard->GetDisableInput())
		return true;

	//update keyboard
	keyboard->Update();

	//check for double input
	for (const auto& doubleComm : DoubleInputCommands)
	{
		auto firstButton = doubleComm.first.first.first;
		auto secondButton = doubleComm.first.second.first;

		switch (doubleComm.first.second.second)
		{
		case SDL_KEYDOWN:
			if (keyboard->IsPressed(firstButton) && keyboard->IsDown(secondButton) || 
				keyboard->IsDown(firstButton) && keyboard->IsPressed(secondButton))
			{
				doubleComm.second->Execute();
				return true;
			}
			break;
		}
	}
	
	for (const auto& comm : KeyboardCommands)
	{
		//update command
		//comm.second->Update();

		auto button = comm.first.first;
		switch (comm.first.second)
		{
		case SDL_KEYDOWN:
			if (keyboard->IsDown(button))
			{
				comm.second->Execute();
			}
			break;
		case SDL_KEYUP:
			if (keyboard->IsUp(button))
			{
				comm.second->Execute();
			}
			break;
		case SDL_KEYMAPCHANGED:
			if (keyboard->IsPressed(button))
			{
				comm.second->Execute();
			}
			break;
		}
	}

	return true;
}


