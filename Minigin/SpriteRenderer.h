#pragma once
#include "RenderComponent.h"
#include <string>

namespace dae
{
	class SpriteRenderer final : public RenderComponent
	{
	public:
		SpriteRenderer(GameObject* pGameObject);

		void SetTexture(std::shared_ptr<dae::Texture2D> texture);
		void SetTexture(const std::string& filename);
	};
}