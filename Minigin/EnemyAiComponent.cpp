#include "EnemyAiComponent.h"
#include "GameObject.h"
#include "CollisionComponent.h"
#include "DeltaTime.h"
#include "TextureComponent.h"
#include "TourretComponent.h"

void dae::EnemyAiComponent::Update()
{
	if(m_Isdead) return;
	HandleMovement();
	glm::vec2 translation{};
	switch (m_Direction)
	{
		case EnemyDirection::Left:
			translation = glm::vec2(m_pOwner.lock().get()->GetLocalPosition()) + (glm::vec2{-1, 0} * m_Speed * dae::DeltaTime::GetInstance().getDeltaTime());
			m_pOwner.lock().get()->SetLocalPosition({ translation.x, translation.y });
			m_pOwner.lock().get()->GetComponent<dae::CollisionComponent>()->SetFuturePos({ translation.x, translation.y });

			m_pOwner.lock().get()->GetComponent<dae::TextureComponent>()->SetAngle(180.f);

			if(m_pOwner.lock().get()->GetComponent<dae::TourretComponent>())
			m_pOwner.lock().get()->GetComponent<dae::TourretComponent>()->SetAngle(180.f);
			break;
		case EnemyDirection::Right:
			translation = glm::vec2(m_pOwner.lock().get()->GetLocalPosition()) + (glm::vec2{ 1, 0 } * m_Speed * dae::DeltaTime::GetInstance().getDeltaTime());
			m_pOwner.lock().get()->SetLocalPosition({ translation.x, translation.y });
			m_pOwner.lock().get()->GetComponent<dae::CollisionComponent>()->SetFuturePos({ translation.x, translation.y });

			m_pOwner.lock().get()->GetComponent<dae::TextureComponent>()->SetAngle(0.f);

			if (m_pOwner.lock().get()->GetComponent<dae::TourretComponent>())
			m_pOwner.lock().get()->GetComponent<dae::TourretComponent>()->SetAngle(0.f);
			break;
		case EnemyDirection::Up:
			translation = glm::vec2(m_pOwner.lock().get()->GetLocalPosition()) + (glm::vec2{ 0, -1 } * m_Speed * dae::DeltaTime::GetInstance().getDeltaTime());
			m_pOwner.lock().get()->SetLocalPosition({ translation.x, translation.y });
			m_pOwner.lock().get()->GetComponent<dae::CollisionComponent>()->SetFuturePos({ translation.x, translation.y });

			m_pOwner.lock().get()->GetComponent<dae::TextureComponent>()->SetAngle(270.f);

			if (m_pOwner.lock().get()->GetComponent<dae::TourretComponent>())
			m_pOwner.lock().get()->GetComponent<dae::TourretComponent>()->SetAngle(270.f);
			break;
		case EnemyDirection::Down:
			translation = glm::vec2(m_pOwner.lock().get()->GetLocalPosition()) + (glm::vec2{ 0, 1 } * m_Speed * dae::DeltaTime::GetInstance().getDeltaTime());
			m_pOwner.lock().get()->SetLocalPosition({ translation.x, translation.y });
			m_pOwner.lock().get()->GetComponent<dae::CollisionComponent>()->SetFuturePos({ translation.x, translation.y });

			m_pOwner.lock().get()->GetComponent<dae::TextureComponent>()->SetAngle(90.f);

			if (m_pOwner.lock().get()->GetComponent<dae::TourretComponent>())
			m_pOwner.lock().get()->GetComponent<dae::TourretComponent>()->SetAngle(90.f);
			break;
	}
}

void dae::EnemyAiComponent::Render()
{
}

void dae::EnemyAiComponent::HandleMovement()
{
	bool m_HasCollidedThisFrame = false;

	if(m_pOwner.lock().get()->GetComponent<dae::CollisionComponent>()->IsColliding() && !m_HasCollidedThisFrame)
	{
		int offset{1};

		switch (m_Direction)
		{
		case EnemyDirection::Left:
			m_Direction = std::rand() % 2 == 0 ? EnemyDirection::Up : EnemyDirection::Down;
			m_pOwner.lock().get()->SetLocalPosition({ m_pOwner.lock().get()->GetLocalPosition().x + offset, m_pOwner.lock().get()->GetLocalPosition().y });
			break;
		case EnemyDirection::Right:
			m_Direction = std::rand() % 2 == 0 ? EnemyDirection::Up : EnemyDirection::Down;
			m_pOwner.lock().get()->SetLocalPosition({ m_pOwner.lock().get()->GetLocalPosition().x - offset, m_pOwner.lock().get()->GetLocalPosition().y });
			break;
		case EnemyDirection::Up:
			m_Direction = std::rand() % 2 == 0 ? EnemyDirection::Left : EnemyDirection::Right;
			m_pOwner.lock().get()->SetLocalPosition({ m_pOwner.lock().get()->GetLocalPosition().x, m_pOwner.lock().get()->GetLocalPosition().y + offset });
			break;
		case EnemyDirection::Down:
			m_Direction = std::rand() % 2 == 0 ? EnemyDirection::Left : EnemyDirection::Right;
			m_pOwner.lock().get()->SetLocalPosition({ m_pOwner.lock().get()->GetLocalPosition().x, m_pOwner.lock().get()->GetLocalPosition().y - offset });
			break;
		}
	}
	else if (!m_pOwner.lock().get()->GetComponent<dae::CollisionComponent>()->IsColliding())
	{
		m_HasCollidedThisFrame = false;
	}
	
}


