#pragma once
#include <Component.h>
#include <vector>
#include <glm/ext/vector_int2.hpp>

namespace pacman
{
	class Selector : public dae::Component
	{
	public:
		Selector(dae::GameObject* pGameObject);
		~Selector() = default;
		
		void AddIndex(const glm::ivec2 pos, unsigned id);
		void SetIndex(unsigned index);
		void Move(int direction);
		void Select();

	private:
		void UpdatePosition();

		std::vector<std::pair<glm::ivec2, unsigned>> m_Indices;
		int m_Index;
	};
}