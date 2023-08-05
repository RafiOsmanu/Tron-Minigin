#include "Input.h"

using namespace dae;

dae::Input::Input()
{
	m_pKeyboard = std::make_shared<Keyboard>();
}

void Input::AddCommand(const ControllerKey& key, std::shared_ptr<Command> command)
{
	m_ControllerCommands[key] = std::move(command);
}

void dae::Input::AddCommand(const KeyboardKey& key, std::shared_ptr<Command> command)
{
	m_KeyboardCommands[key] = std::move(command);
}

void dae::Input::AddCommand(const DoubleInput& doubleKey, std::shared_ptr<Command> command)
{
	m_DoubleInputCommands[doubleKey] = std::move(command);
}


