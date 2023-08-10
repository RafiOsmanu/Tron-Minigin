#include "TextureComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

void dae::TextureComponent::Update()
{
}

void dae::TextureComponent::Render() 
{
	if(m_IsDead) return;
	const auto& pos = m_pOwner.lock()->GetWorldPosition();
	
	if (m_SimpleTexture)
	{
		Renderer::GetInstance().RenderTexture(*m_texture, pos.x - 8.f, pos.y - 8.f, m_Angle, false);
	}
	else
	{
		Renderer::GetInstance().RenderTexture(*m_texture, pos.x - 8.f, pos.y - 8.f, m_Width, m_Height, m_Angle, false);
	}
	
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

