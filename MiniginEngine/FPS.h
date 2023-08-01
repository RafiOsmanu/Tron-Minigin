#pragma once
#include <memory>
#include "BaseComponent.h"
#include "GameObject.h"

namespace dae
{
	class FPS : public BaseComponent
	{
		std::weak_ptr<GameObject> m_pOwner;
	public:
		explicit FPS(std::shared_ptr<GameObject> pOwner) : m_pOwner(pOwner) {};

		FPS(const FPS& other) = delete;
		FPS(FPS&& other) = delete;
		FPS& operator=(const FPS& other) = delete;
		FPS& operator=(FPS&& other) = delete;

		virtual void Update() override;
		virtual void Render() override;
		float GetFPS();

	protected:
		
		std::weak_ptr<GameObject> GetOwner() const { return m_pOwner; }
		float m_Timer = 0.f;
		const int m_SampleAmount = 10;
		std::vector<float> m_FpsSample;
	};
}

