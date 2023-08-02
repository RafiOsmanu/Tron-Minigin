#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"


namespace dae
{
	GameObject::~GameObject() = default;

	void GameObject::Update()
	{
		for (const auto& component : m_Components)
		{
			component->Update();
		}

		//if (m_IsPositionDirty)
		{
			for (auto child : m_pChildren)
			{
				child.lock()->Update();
			}
		}
		
	}

	void GameObject::Render() const
	{ 
		for (const auto& component : m_Components)
		{
			component->Render();
		}
	}

	/*void GameObject::SetPosition(float x, float y)
	{
		m_transform.SetPosition(x, y, 0.0f);
		
	}

	glm::vec3 GameObject::GetPosition()
	{
		return m_transform.GetPosition();
	}*/


	void GameObject::AddComponent(std::shared_ptr<BaseComponent> component)
	{
		m_Components.emplace_back(component);
	}

	void GameObject::SetParent(std::shared_ptr<GameObject> parent, bool keepWorldPos)
	{
		if (parent.get() == nullptr)
		{
			SetLocalPosition(GetWorldPosition());
		}
		else
		{
			if (keepWorldPos && m_pParent.lock())
			{
				SetLocalPosition(GetLocalPosition() - parent->GetWorldPosition());
			}

			//set dirty flag
			SetPositionDirty();
		}

		if (m_pParent.lock())
		//remove child current game object from parent if any
		m_pParent.lock()->RemoveChild(shared_from_this());

		//set parent
		m_pParent = parent;

		if (m_pParent.lock())
		{
			m_pParent.lock()->AddChild(shared_from_this());
		}
	}

	void GameObject::SetLocalPosition(const glm::vec2& pos)
	{
		m_LocalPos = pos;
		SetPositionDirty();
	}

	const glm::vec2& GameObject::GetWorldPosition() 
	{
		// TODO: insert return statement here
		if (m_IsPositionDirty)
		{
			UpdateWorldPos();
		}
		return m_WorldPos;
	}

	const glm::vec2& GameObject::GetLocalPosition() const
	{
		return m_LocalPos;
	}

	void GameObject::UpdateWorldPos()
	{
		if (m_IsPositionDirty)
		{
			if (m_pParent.lock() == nullptr)
			{
				m_WorldPos = m_LocalPos;
			}
			else
			{
				m_WorldPos = m_pParent.lock()->GetWorldPosition() + m_LocalPos;
			}
		}
		m_IsPositionDirty = false;
	}


	void GameObject::RemoveChild(std::shared_ptr<GameObject> child)
	{
		int check{};
		for (const auto& kid : m_pChildren)
		{
			if (kid.lock() == child)
			{
				m_pChildren.erase(m_pChildren.begin() + check);
				kid.lock()->m_pParent.lock() = nullptr;
				return;
			}
			++check;
		}
	}

	void GameObject::AddChild(std::shared_ptr<GameObject> child)
	{
		m_pChildren.emplace_back(child);
	}

	void GameObject::SetPositionDirty()
	{
		m_IsPositionDirty = true;

		for (auto child : m_pChildren)
		{
			child.lock()->SetPositionDirty();
		}
	}

	

	
	
}