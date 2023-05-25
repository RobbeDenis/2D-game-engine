#pragma once
#include "Component.h"
#include <SDL_rect.h>
#include <string>
#include <functional>
#include <glm/vec2.hpp>

namespace dae
{
	class Collider : public Component
	{
	public:
		Collider(GameObject* pGameObject);
		virtual ~Collider();

		void Loaded() override;
		void SetDimensions(const SDL_Rect& rect);
		void SetDimensions(int w, int h);
		void SetTag(const std::string& tag);
		void SetOffset(int x, int y);

		bool IsOverlappingWith(Collider* other);
		const std::string& GetTag() const;
		const std::vector<Collider*>& GetColliders();

	private:
		const SDL_Rect& GetRect();

		std::string m_Tag;
		SDL_Rect m_Rect;
		glm::ivec2 m_Offset;
	};
}