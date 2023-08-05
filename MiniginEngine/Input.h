#pragma once
#include<iostream>
#include <cstdlib>
#include <map>
#include <vector>

#include "Gamepad.h"
#include "Command.h"
#include "SDL.h"

#include "Singleton.h"

#include "Keyboard.h"

namespace dae
{
	
	class Input : public Singleton<Input>
	{
	public:

		Input();
		~Input() = default;

		//std::pair<CONTROLLER INDEX, CONTROLLER BUTTON>
		using ControllerKey = std::pair<unsigned, Gamepad::ControllerButton>;

		//u map the controller with ||certain index paired to button|| to a command that needs to be executed
		using ControllerCommandsMap = std::map<ControllerKey, std::shared_ptr<Command>>;

		using KeyboardKey = std::pair <SDL_Scancode, SDL_EventType>;
		using KeyboardCommandsMap = std::map<KeyboardKey, std::shared_ptr<Command>>;
		//double input two keys pressed at the same time
		using DoubleInput = std::pair<KeyboardKey, KeyboardKey>;
		using DoubleInputCommandsMap = std::map<DoubleInput, std::shared_ptr<Command>>;

		


		//SET
		void AddCommand(const ControllerKey& key, std::shared_ptr<Command> command);
		void AddCommand(const KeyboardKey& key, std::shared_ptr<Command> command);
		void AddCommand(const DoubleInput& doubleKey, std::shared_ptr<Command> command);

		void AddController(std::shared_ptr<Gamepad> controller) { m_Controllers.push_back(controller); }

		//GET
		const ControllerCommandsMap& GetControllerCommands() const { return m_ControllerCommands; }
		const KeyboardCommandsMap& GetKeyboardCommands() const { return m_KeyboardCommands; }
		std::vector<std::shared_ptr<Gamepad>> GetControllers() const{ return m_Controllers; }
		std::shared_ptr<Keyboard> GetKeyboard() const { return m_pKeyboard; }
		const DoubleInputCommandsMap& GetDoubleInputCommands() const { return m_DoubleInputCommands; }

	private:

		ControllerCommandsMap m_ControllerCommands{};
		KeyboardCommandsMap m_KeyboardCommands{};
		DoubleInputCommandsMap m_DoubleInputCommands{};

		std::vector<std::shared_ptr<Gamepad>> m_Controllers{};
		std::shared_ptr<Keyboard> m_pKeyboard;

	};
}

