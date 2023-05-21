#include "StateMachine.h"

pacman::StateMachine::StateMachine()
	: m_State{ -1 }
	, m_EnterState{ }
	, m_UpdateState{ }
	, m_ExitState{ }
{

}

void pacman::StateMachine::AddState(int state, const std::function<void()>& enter, const std::function<void()>& update, const std::function<void()>& exit)
{
	m_EnterState[state] = enter;
	m_UpdateState[state] = update;
	m_ExitState[state] = exit;
}

void pacman::StateMachine::SetState(int state)
{
	if (m_State != -1)
	{
		if (m_ExitState[m_State])
			m_ExitState[m_State]();
	}

	m_State = state;
	if (m_EnterState[m_State])
		m_EnterState[m_State]();
}

void pacman::StateMachine::UpdateState()
{
	if (m_State == -1)
		return;

	if (m_UpdateState[m_State])
		m_UpdateState[m_State]();
}