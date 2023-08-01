#pragma once
#include <memory>

namespace dae
{

	class Gamepad 
	{
	public:
		explicit Gamepad(int controllerIndex);
		~Gamepad();

		enum class ControllerButton
		{
			DPadUp = 0x0001,
			DPadDown = 0x0002,
			DPadLeft = 0x0004,
			DPadRight = 0x0008,
			Start = 0x0010,
			Back = 0x0020,
			LeftThumb = 0x0040,
			RightThumb = 0x0080,
			LeftShoulder = 0x0100,
			RightShoulder = 0x0200,
			ButtonSouth = 0x1000,
			ButtonEast = 0x2000,
			ButtonWest = 0x4000,
			ButtonNorth = 0x8000
		};

		void Update();

		bool IsDownThisFrame(ControllerButton button) const;

		bool IsUpThisFrame(ControllerButton button) const;

		bool IsPressed(ControllerButton button) const;

	private:
		class ControllerImpl;
		std::unique_ptr<ControllerImpl> m_pImpl;
	};
}

