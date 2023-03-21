#pragma once
#include "Component.h"
#include "Texture2D.h"

namespace dae
{
	class RenderComponent : public Component
	{
	public:
		RenderComponent(GameObject* pGameObject);
		~RenderComponent();

		void Loaded() override;
		virtual void Render() const;

	protected:
		std::shared_ptr<Texture2D> m_pTexture;
	};
}
