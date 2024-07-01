#pragma once
#include "Observer.h"
#include <vector>

class Subject {
	std::vector<Observer*> activeObservers;
	
public:
	void addObserver(Observer* observer) { activeObservers.push_back(observer); };
	void removeObserver(Observer* observer) {
		for (int i = 0; i < activeObservers.size(); i++) {
			if (activeObservers[i] == observer) {
				for (i; i < activeObservers.size() - 1; i++)
					activeObservers[i] = activeObservers[i + 1];
			}
		}
	};
	void notifyObservers() {
		for (auto i : activeObservers)
			i->update();
	};
	//virtual ~Subject()
};