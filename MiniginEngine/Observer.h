#pragma once
#include "BaseComponent.h"
#include"DataTypes.h"
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
	};
}

