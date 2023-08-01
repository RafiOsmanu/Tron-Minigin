#pragma once
#include <memory>
#include "Transform.h"
#include <vector>
#include "BaseComponent.h"
#include <string>


namespace dae
{
	class Texture2D;

	// todo: this should become final.
	class GameObject final : public std::enable_shared_from_this<GameObject>
	{
	public:
		virtual void Update();
		virtual void Render() const;
		void AddComponent(std::shared_ptr<BaseComponent> component);
		void SetParent(std::shared_ptr <GameObject> parent, bool keepWorldPos = true);
		void SetLocalPosition(const glm::vec2& pos);
		const glm::vec2& GetWorldPosition() ;
		const glm::vec2& GetLocalPosition() const;
		void UpdateWorldPos();
		void RemoveChild(std::shared_ptr <GameObject> child);
		void AddChild(std::shared_ptr <GameObject> child);
		void SetPositionDirty();
		bool HasParent() {return m_pParent.lock() != nullptr; }
		bool IsMoving() { return m_IsMoving; }
		void SetIsMoving(bool isMoving) { m_IsMoving = isMoving; }
		

		template <typename T> std::shared_ptr<T> GetComponent()
		{
			for (auto& component : m_Components) {
				if (std::dynamic_pointer_cast<T>(component)) {
					return std::dynamic_pointer_cast<T>(component);
				}
			}
			return nullptr;
		}

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform m_transform{};
		// todo: mmm, every gameobject has a texture? Is that correct?
		std::vector<std::shared_ptr<BaseComponent>> m_Components;

		glm::vec2 m_LocalPos{};
		glm::vec2 m_WorldPos{};

		std::weak_ptr <GameObject> m_pParent;
		std::vector<std::weak_ptr <GameObject>> m_pChildren;
		bool m_IsMoving = false;

		bool m_IsPositionDirty = false;


	};
	
	

}


