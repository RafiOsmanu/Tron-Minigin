#include "EnemyAiComponent.h"
#include "GameObject.h"
#include "CollisionComponent.h"
#include "DeltaTime.h"

void dae::EnemyAiComponent::Update()
{
	if(m_Isdead) return;
	HandleMovement();
	glm::vec2 translation{};
	switch (m_Direction)
	{
		case EnemyDirection::Left:
			translation = glm::vec2(m_pOwner.lock().get()->GetLocalPosition()) + (glm::vec2{-1, 0} * 50.f * dae::DeltaTime::GetInstance().getDeltaTime());
			m_pOwner.lock().get()->SetLocalPosition({ translation.x, translation.y });
			m_pOwner.lock().get()->GetComponent<dae::CollisionComponent>()->SetFuturePos({ translation.x, translation.y });
			break;
		case EnemyDirection::Right:
			translation = glm::vec2(m_pOwner.lock().get()->GetLocalPosition()) + (glm::vec2{ 1, 0 } * 50.f * dae::DeltaTime::GetInstance().getDeltaTime());
			m_pOwner.lock().get()->SetLocalPosition({ translation.x, translation.y });
			m_pOwner.lock().get()->GetComponent<dae::CollisionComponent>()->SetFuturePos({ translation.x, translation.y });
			break;
		case EnemyDirection::Up:
			translation = glm::vec2(m_pOwner.lock().get()->GetLocalPosition()) + (glm::vec2{ 0, -1 } * 50.f * dae::DeltaTime::GetInstance().getDeltaTime());
			m_pOwner.lock().get()->SetLocalPosition({ translation.x, translation.y });
			m_pOwner.lock().get()->GetComponent<dae::CollisionComponent>()->SetFuturePos({ translation.x, translation.y });
			break;
		case EnemyDirection::Down:
			translation = glm::vec2(m_pOwner.lock().get()->GetLocalPosition()) + (glm::vec2{ 0, 1 } * 50.f * dae::DeltaTime::GetInstance().getDeltaTime());
			m_pOwner.lock().get()->SetLocalPosition({ translation.x, translation.y });
			m_pOwner.lock().get()->GetComponent<dae::CollisionComponent>()->SetFuturePos({ translation.x, translation.y });
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
		//int minRange = 0;
		//int maxRange = 3;
		//std::set<int> excludedNumbers{};
		//int randomExcludedNumber{};

		switch (m_Direction)
		{
		case EnemyDirection::Left:
			m_Direction = std::rand() % 2 == 0 ? EnemyDirection::Up : EnemyDirection::Down;
			m_pOwner.lock().get()->SetLocalPosition({ m_pOwner.lock().get()->GetLocalPosition().x + 1, m_pOwner.lock().get()->GetLocalPosition().y });
			/*excludedNumbers = { 0 };
			randomExcludedNumber = getRandomNumberExcluding(minRange, maxRange, excludedNumbers);
			m_Direction = static_cast<EnemyDirection>(randomExcludedNumber);*/
			break;
		case EnemyDirection::Right:
			m_Direction = std::rand() % 2 == 0 ? EnemyDirection::Up : EnemyDirection::Down;
			m_pOwner.lock().get()->SetLocalPosition({ m_pOwner.lock().get()->GetLocalPosition().x - 1, m_pOwner.lock().get()->GetLocalPosition().y });
			/*excludedNumbers = { 1 };
			randomExcludedNumber = getRandomNumberExcluding(minRange, maxRange, excludedNumbers);
			m_Direction = static_cast<EnemyDirection>(randomExcludedNumber);*/
			break;
		case EnemyDirection::Up:
			m_Direction = std::rand() % 2 == 0 ? EnemyDirection::Left : EnemyDirection::Right;
			m_pOwner.lock().get()->SetLocalPosition({ m_pOwner.lock().get()->GetLocalPosition().x, m_pOwner.lock().get()->GetLocalPosition().y + 1 });
			/*excludedNumbers = { 2 };
			randomExcludedNumber = getRandomNumberExcluding(minRange, maxRange, excludedNumbers);
			m_Direction = static_cast<EnemyDirection>(randomExcludedNumber);*/
			break;
		case EnemyDirection::Down:
			m_Direction = std::rand() % 2 == 0 ? EnemyDirection::Left : EnemyDirection::Right;
			m_pOwner.lock().get()->SetLocalPosition({ m_pOwner.lock().get()->GetLocalPosition().x, m_pOwner.lock().get()->GetLocalPosition().y - 1 });
			/*excludedNumbers = { 3 };
			randomExcludedNumber = getRandomNumberExcluding(minRange, maxRange, excludedNumbers);
			m_Direction = static_cast<EnemyDirection>(randomExcludedNumber);*/
			break;
		}
	}
	else if (!m_pOwner.lock().get()->GetComponent<dae::CollisionComponent>()->IsColliding())
	{
		m_HasCollidedThisFrame = false;
	}
	
}


