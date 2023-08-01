#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>
#include <iostream>
#pragma comment(lib, "xinput.lib")

#include "Gamepad.h"

class dae::Gamepad::ControllerImpl
{
	XINPUT_STATE m_PreviousState{};
	XINPUT_STATE m_CurrentState{};

	WORD m_ButtonPressedThisFrame{};
	WORD m_ButtonReleasedThisFrame{};

	int m_ControllerIndex;
public:

	ControllerImpl(int controllerIndex)
		:m_ControllerIndex{controllerIndex}
	{
		ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	}

	void Update()
	{
		CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
		XInputGetState(m_ControllerIndex, &m_CurrentState);

		auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;

		m_ButtonPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
		m_ButtonReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
	}

	bool IsDownThisFrame(ControllerButton button) const
	{
		return m_ButtonPressedThisFrame & static_cast<unsigned int>(button);
	}

	bool IsUpThisFrame(ControllerButton button) const
	{
		return m_ButtonReleasedThisFrame & static_cast<unsigned int>(button);
	}

	bool IsPressed(ControllerButton button) const
	{
		return m_CurrentState.Gamepad.wButtons & static_cast<unsigned int>(button);
	}
};

dae::Gamepad::Gamepad(int controllerIndex)
	:m_pImpl{std::make_unique<ControllerImpl>(controllerIndex)} {}

dae::Gamepad::~Gamepad() = default;

void dae::Gamepad::Update()
{
	m_pImpl->Update();
}

bool dae::Gamepad::IsDownThisFrame(ControllerButton button) const
{
	return m_pImpl->IsDownThisFrame(button);
}

bool dae::Gamepad::IsUpThisFrame(ControllerButton button) const
{
	return m_pImpl->IsUpThisFrame(button);
}

bool  dae::Gamepad::IsPressed(ControllerButton button) const
{
	return m_pImpl->IsPressed(button);
}


