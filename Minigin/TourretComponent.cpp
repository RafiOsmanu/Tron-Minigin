#include "TourretComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

void dae::TourretComponent::Update()
{
}

void dae::TourretComponent::Render()
{
	const auto& pos = m_pOwner.lock()->GetWorldPosition();
	Renderer::GetInstance().RenderTexture(*m_texture, pos.x - 8, pos.y - 8, m_Angle, m_Mirror);
}

void dae::TourretComponent::SetTexture(const std::string& filename)
{
	m_TexturePath = filename;
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);

}
