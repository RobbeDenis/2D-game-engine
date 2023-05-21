#pragma once
#include <unordered_map>
#include <functional>

namespace pacman
{
	class StateMachine
	{
	protected:
		StateMachine();

		void AddState(int state, const std::function<void()>& enter, const std::function<void()>& update, const std::function<void()>& exit);
		void SetState(int state);
		void UpdateState();

	private:
		std::unordered_map<int, std::function<void()>> m_UpdateState;
		std::unordered_map<int, std::function<void()>> m_EnterState;
		std::unordered_map<int, std::function<void()>> m_ExitState;
		int m_State;
	};
}