#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Xinput.h>
#pragma comment(lib, "xinput.lib")

#include "XBox360Controller.h"

class xbox::XBox360Controller::XBox360ControllerImpl
{
public:
	XBox360ControllerImpl(int controllerIndex)
		: m_ControllerIndex{ controllerIndex }
	{
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_PrevState, sizeof(XINPUT_STATE));
	}

	void ProcessInput()
	{
		CopyMemory(&m_PrevState, &m_CurrentState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		XInputGetState(m_ControllerIndex, &m_CurrentState);

		WORD buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PrevState.Gamepad.wButtons;
		m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
		m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
	}

	bool IsPressed(unsigned button) const { return m_ButtonsPressedThisFrame & button; };
	bool IsReleased(unsigned button) const { return m_ButtonsReleasedThisFrame & button; };
	bool IsDown(unsigned button) const { return m_CurrentState.Gamepad.wButtons & button; };

private:
	XINPUT_STATE m_CurrentState{};
	XINPUT_STATE m_PrevState{};
	WORD m_ButtonsPressedThisFrame{};
	WORD m_ButtonsReleasedThisFrame{};
	int m_ControllerIndex{};
};

xbox::XBox360Controller::XBox360Controller(unsigned controllerIndex)
{
	m_pImpl = new XBox360ControllerImpl(controllerIndex);
}

xbox::XBox360Controller::~XBox360Controller()
{
	delete m_pImpl;
}

void xbox::XBox360Controller::ProcessInput()
{
	m_pImpl->ProcessInput();
}

bool xbox::XBox360Controller::IsPressed(unsigned button) const
{
	return m_pImpl->IsPressed(button);
};

bool xbox::XBox360Controller::IsReleased(unsigned button) const
{
	return m_pImpl->IsReleased(button);
};

bool xbox::XBox360Controller::IsDown(unsigned button) const
{
	return m_pImpl->IsDown(button);
};