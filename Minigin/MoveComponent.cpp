#include "MoveComponent.h"
#include "DeltaTime.h"
#include <cmath>

void dae::MoveComponent::Update()
{
	//m_PosX += 20.f * DeltaTime::GetInstance().getDeltaTime();
	

	if (m_pOwner.lock()->HasParent())
	{
		m_Angle += 8.f * DeltaTime::GetInstance().getDeltaTime(); 
		m_PosX = (15.f + m_Radius) * std::sinf(m_Angle);
		m_PosY = (15.f + m_Radius) * std::cosf(m_Angle);
	}
	else
	{
		glm::vec2 CenterPoint = m_pOwner.lock()->GetWorldPosition();
		m_Angle += 4.f * DeltaTime::GetInstance().getDeltaTime();
		m_PosX = CenterPoint.x + m_Radius * std::sinf(m_Angle) ;
		m_PosY = CenterPoint.y + m_Radius * std::cosf(m_Angle) ;
	}
	
	m_pOwner.lock()->SetLocalPosition({ m_PosX, m_PosY });
}

void dae::MoveComponent::Render()
{

}


