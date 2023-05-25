#pragma once
#include "Component.h"
#include <SDL_rect.h>
#include <string>
#include <functional>

namespace dae
{
	class Collider : public Component
	{
	public:
		Collider(GameObject* pGameObject);

		void Loaded() override;
		void SetDimensions(const SDL_Rect& rect);
		void SetDimensions(int x, int y, int w, int h);
		void SetTag(const std::string& tag);

		bool IsOverlappingWith(Collider* other);
		const SDL_Rect& GetRect() const;
		std::vector<Collider*>& GetColliders();

	private:
		std::string m_Tag;
		SDL_Rect m_Rect;
	};
}