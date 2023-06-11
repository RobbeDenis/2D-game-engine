#pragma once
#include "Controller.h"

namespace xbox
{
	enum XBoxButton
	{
		ButtonA = 0x1000,
		ButtonB = 0x2000,
		ButtonX = 0x4000,
		ButtonY = 0x8000,
		ButtonUp = 0x0001,
		ButtonDown = 0x0002,
		ButtonLeft = 0x0004,
		ButtonRight = 0x0008,
		Start = 0x0010,
		Back = 0x0020,
		LeftStick = 0x0040,
		RightStick = 0x0080,
		LeftBumper = 0x0100,
		RightBumper = 0x0200,
	};

	class XBox360Controller : public Controller 
	{
	public:
		explicit XBox360Controller(unsigned controllerIndex);
		~XBox360Controller();

		void ProcessInput() override;

		bool IsPressed(unsigned button) const override;
		bool IsReleased(unsigned button) const override;
		bool IsDown(unsigned button) const override;

		int GetIndex() const override;

	private:
		class XBox360ControllerImpl;
		XBox360ControllerImpl* m_pImpl;
	};
}