#include "StateMachine.h"

dae::StateMachine::StateMachine()
	: m_State{ -1 }
	, m_EnterState{ }
	, m_UpdateState{ }
	, m_ExitState{ }
{

}

void dae::StateMachine::AddState(int state, const std::function<void()>& enter, const std::function<void()>& update, const std::function<void()>& exit)
{
	m_EnterState.emplace(state, enter);
	m_UpdateState.emplace(state, update);
	m_ExitState.emplace(state, exit);
}

void dae::StateMachine::SetState(int state)
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

void dae::StateMachine::UpdateState()
{
	if (m_State == -1)
		return;

	if (m_UpdateState[m_State])
		m_UpdateState[m_State]();
}