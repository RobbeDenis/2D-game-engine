#include "RotateParent.h"
#include "GameObject.h"
#include "ETime.h"

dae::RotateParent::RotateParent(GameObject* pGameObject)
	: Component(pGameObject)
	, m_Speed{ 1.f }
	, m_Direction{ 1 }
{
}

void dae::RotateParent::Update()
{
	const float pi = 3.141592f;
	float radians = m_Direction * (ETime::GetInstance().GetDeltaTime() * m_Speed);
	
	while (radians > 2 * pi)
		radians -= radians;

	glm::vec3 pos = GetGameObject()->GetLocalPosition();
	glm::vec3 newPos
	{
		pos.x * glm::cos(radians) - pos.y * glm::sin(radians),
		pos.x * glm::sin(radians) + pos.y * glm::cos(radians),
		0.f
	};

	GetGameObject()->SetLocalPosition(newPos);

}

void dae::RotateParent::SetSpeed(float speed)
{
	m_Speed = speed;
}

void dae::RotateParent::SetDirection(int direction)
{
	glm::clamp(direction, -1, 1);
	m_Direction = direction;
}

