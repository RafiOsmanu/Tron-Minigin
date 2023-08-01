#pragma once
#include "SDL.h"
#include <memory>

class Keyboard
{
public:
	
	Keyboard();
	~Keyboard();
	Keyboard(const Keyboard& other) = delete;
	Keyboard(Keyboard&& other) = delete;
	Keyboard& operator=(const Keyboard& other) = delete;
	Keyboard& operator=(Keyboard&& other) = delete;

	void Update();
	bool IsDown(int button) const { return m_pCurrentKeyboardState[button] && !m_pPreviousKeyboardState[button]; }
	bool IsUp(int button) const { return !m_pCurrentKeyboardState[button] && m_pPreviousKeyboardState[button]; }
	bool IsPressed(int button) const { return m_pCurrentKeyboardState[button]; }
	void SetDisableInput(bool disable) { m_DisableInput = disable; }
	bool GetDisableInput() const { return m_DisableInput; }

private:
	Uint8* m_pPreviousKeyboardState;
	Uint8* m_pCurrentKeyboardState; 
	bool m_DisableInput{ false };




};

