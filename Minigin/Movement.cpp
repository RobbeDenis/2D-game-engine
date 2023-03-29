#include "Movement.h"
#include "ETime.h"
#include "GameObject.h"

dae::Movement::Movement(GameObject* gameObject)
	: Component(gameObject)
	, m_Direction{0.f,0.f}
	, m_MovementSpeed{100.f}
	, m_ShouldMove{false}
{
}

void dae::Movement::Update()
{
	if (!m_ShouldMove)
		return;

	const float deltaTime = ETime::GetInstance().GetDeltaTime();
	glm::vec3 newPos = GetGameObject()->GetLocalPosition();
	newPos.x += m_Direction.x * m_MovementSpeed * deltaTime;
	newPos.y += m_Direction.y * m_MovementSpeed * deltaTime;
	GetGameObject()->SetLocalPosition(newPos);

	m_ShouldMove = false;
}

void dae::Movement::Move(int x, int y)
{
	m_ShouldMove = true;
	m_Direction.x = static_cast<float>(x);
	m_Direction.y = static_cast<float>(y);
	m_Direction = glm::normalize(m_Direction);
}
