#pragma once
#include "Component.h"
#include <vector>
#include <glm/glm.hpp>
#include "SpriteRenderer.h"

namespace dae
{
	class Animator final : public Component
	{
	public:
		Animator(dae::GameObject* gameObject);

		void Loaded() override;
		void Update() override;
		void AddAnimation(const unsigned id, const int nrOffFrames, const glm::ivec2& srcPos, const int srcWidth, const int srcHeight, const float TimePerFrame = 0.250f, const bool loop = true, SDL_RendererFlip flip = SDL_FLIP_NONE);
		void SetAnimation(const unsigned id);
		void SetDst(const SDL_Rect& dst);
		void Mirror(bool mirror);
		void Pause();
		void Play();

	private:
		struct AnimationData
		{
			glm::ivec2 SrcPos = {0, 0};
			int SrcWidth = 0;
			int SrcHeight = 0;
			float TimePerFrame = 0;
			unsigned Id = 0;
			SDL_RendererFlip SdlFlip = SDL_FLIP_NONE;
			int NrOffFrames = 0;
			bool Loop = false;
		};

		std::vector<AnimationData> m_Animations;
		SpriteRenderer* m_pSprite;

		glm::vec2 m_DstPos;
		float m_DstWidth;
		float m_DstHeight;
		float m_ElapsedTime;
		unsigned m_CurrentAnimationIndex;
		int m_CurrentFrame;
		bool m_Pause;
		bool m_Mirror;
	};
}

