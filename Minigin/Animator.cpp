#include "Animator.h"
#include "ETime.h"
#include "GameObject.h"

dae::Animator::Animator(dae::GameObject* gameObject)
	: Component(gameObject)
	, m_pSprite{ nullptr }
	, m_CurrentAnimationIndex{ 0 }
	, m_CurrentFrame{ 0 }
	, m_DstHeight{ 0 }
	, m_DstWidth{ 0 }
	, m_ElapsedTime{ 0 }
	, m_Pause{ false }
	, m_DstPos{ }
{

}

void dae::Animator::Loaded()
{
	m_pSprite = GetGameObject()->GetComponent<SpriteRenderer>();
	m_pSprite->UseSrc(true);
}

void dae::Animator::SetDst(const SDL_Rect& dst)
{
	m_pSprite->SetDst(dst);
}

void dae::Animator::Mirror(bool mirror)
{
	m_Mirror = mirror;
}

void dae::Animator::Pause()
{
	m_Pause = true;
}

void dae::Animator::Play()
{
	m_Pause = false;
}

void dae::Animator::AddAnimation(const unsigned id, const int nrOffFrames, const glm::ivec2& srcPos, const int srcWidth, const int srcHeight, const float TimePerFrame, const bool loop, SDL_RendererFlip flip)
{
	AnimationData animation;
	animation.Id = id;
	animation.NrOffFrames = nrOffFrames;
	animation.SrcPos = srcPos;
	animation.SrcHeight = srcHeight;
	animation.SrcWidth = srcWidth;
	animation.TimePerFrame = TimePerFrame;
	animation.Loop = loop;
	animation.SdlFlip = flip;

	m_Animations.push_back(animation);
}

void dae::Animator::SetAnimation(const unsigned id)
{
	if (m_CurrentAnimationIndex == id)
		return;

	for (unsigned i = 0; i < m_Animations.size(); ++i)
	{
		if (m_Animations[i].Id == id)
		{
			m_CurrentAnimationIndex = i;

			m_pSprite->SetSrc(
				{ m_Animations[i].SrcPos.x,
				  m_Animations[i].SrcPos.y,
				  m_Animations[i].SrcWidth,
				  m_Animations[i].SrcHeight });

			m_ElapsedTime = 0.f;
			m_CurrentFrame = 0;
			m_Pause = false;
		}
	}
}

void dae::Animator::Update()
{
	if (m_Pause || m_Animations.empty())
		return;

	const AnimationData& animation = m_Animations[m_CurrentAnimationIndex];

	// Return if animation only has 1 frame
	// Return if animation enden and doesn't loop
	if (animation.NrOffFrames <= 1 || (!animation.Loop && m_CurrentFrame >= animation.NrOffFrames))
		return;

	m_ElapsedTime += ETime::GetInstance().GetDeltaTime();

	while (m_ElapsedTime >= animation.TimePerFrame)
	{
		++m_CurrentFrame;
		if (m_CurrentFrame >= animation.NrOffFrames)
		{
			if (!animation.Loop)
				return;

			m_CurrentFrame = 0;
		}

		m_pSprite->SetSrc({
			animation.SrcPos.x + (m_CurrentFrame * animation.SrcWidth),
			animation.SrcPos.y,
			animation.SrcWidth,
			animation.SrcHeight });

		if (m_Mirror)
			m_pSprite->SetFlip(animation.SdlFlip);
		else
			m_pSprite->SetFlip(SDL_FLIP_NONE);

		m_ElapsedTime -= animation.TimePerFrame;
	}
}