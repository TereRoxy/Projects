#pragma once

#include "Event.h"
#include "DynamicArray.h"
#include "DynamicArray.cpp"

class Repository {
private:
	DynamicArray<Event> events;
	//DynamicArray events;
public:
	//Constructor
	Repository(){};
	//Destructor
	~Repository(){};
	//Copy constructor
	Repository(const Repository& other) : events(other.events) {}
	//Add an event to the repository
	void addEvent(const Event& e);
	//Update an event from the repository
	void updateEvent(const Event& e, int index);
	//Delete an event from the repository
	void deleteEvent(int index);
	//Get the events from the repository
	DynamicArray<Event> getEvents();
	//DynamicArray getEvents();
	//Get the size of the repository
	int getSize();
	//Get the event from the repository by index
	Event getEvent(int index);
	//Get the index of an event from the repository
	int getIndex(const Event& e);
	//Assignment operator
	Repository& operator=(const Repository& r);
	//ToString
	string toString();
	void load_events();
};
	