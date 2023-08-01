#include "Keyboard.h"

Keyboard::Keyboard()
{
	m_pCurrentKeyboardState = new Uint8[SDL_NUM_SCANCODES];
	m_pPreviousKeyboardState = new Uint8[SDL_NUM_SCANCODES];

	memcpy(m_pPreviousKeyboardState, SDL_GetKeyboardState(nullptr), SDL_NUM_SCANCODES);
	memcpy(m_pCurrentKeyboardState, SDL_GetKeyboardState(nullptr), SDL_NUM_SCANCODES);

}

Keyboard::~Keyboard()
{
	delete[] m_pCurrentKeyboardState;
	delete[] m_pPreviousKeyboardState;
}

void Keyboard::Update()
{
	memcpy(m_pPreviousKeyboardState, m_pCurrentKeyboardState, SDL_NUM_SCANCODES);
	memcpy(m_pCurrentKeyboardState, SDL_GetKeyboardState(nullptr), SDL_NUM_SCANCODES);
}
