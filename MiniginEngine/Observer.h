#pragma once
#include "BaseComponent.h"
#include"DataTypes.h"
#include "../Minigin/BlackBoard.h"
namespace dae
{
	class Observer
	{
	public:
		Observer() {};
		virtual ~Observer() = default;
		Observer(const Observer&) = delete;
		Observer(Observer&&) = delete;
		Observer& operator= (const Observer&) = delete;
		Observer& operator= (const Observer&&) = delete;

		virtual void Notify(EventType eventType) = 0;
		virtual void Notify(EventType eventType, std::shared_ptr<BlackBoard> blackboard) = 0;
	};
}

