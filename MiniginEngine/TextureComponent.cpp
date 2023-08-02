#include "TextureComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

void dae::TextureComponent::Update()
{
}

void dae::TextureComponent::Render() 
{
	const auto& pos = m_pOwner.lock()->GetWorldPosition();
	Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y, m_Angle, false);
	
}

void dae::TextureComponent::SetTexture(const std::string& filename)
{
	m_TexturePath = filename;
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
	
}

std::string dae::TextureComponent::GetTexture() const
{
	return m_TexturePath;
}

