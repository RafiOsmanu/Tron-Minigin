#pragma once
#include <vector>
#include <memory> 
#include<algorithm>
#include "Observer.h"

namespace dae
{
	class Subject final
	{
	public:
		//observer code

		void AddObserver(std::shared_ptr<Observer> observer) {
			m_observers.push_back(observer);
		}

		void RemoveObserver(std::shared_ptr<Observer> observer) {
			m_observers.erase(std::remove(m_observers.begin(), m_observers.end(), observer), m_observers.end());
		}

		// Method to notify observers of player death
		void NotifyObservers(EventType eventType) {
			for (auto observer : m_observers) {
				observer->Notify(eventType);
			}
		}
	private:

		//vector of observers
		std::vector<std::shared_ptr<Observer>> m_observers;
	};
}

