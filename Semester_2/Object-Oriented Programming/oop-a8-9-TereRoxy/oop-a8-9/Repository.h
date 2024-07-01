#pragma once

#include <vector>
#include "Event.h"
#include "FileFormat.h"

class Repository {
private:
	std::vector<Event> events;
	FileFormat* fileFormat = nullptr;
	
	//DynamicArray events;
public:
	//Constructor
	Repository(){};
	Repository(FileFormat* format) : fileFormat{ format } {}
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
	std::vector<Event> getEvents();
	//DynamicArray getEvents();
	//Get the size of the repository
	int getSize();
	//Get the event from the repository by index
	Event getEvent(int index);
	//Get the index of an event from the repository
	int getIndex(const Event& e);
	//Assignment operator
	//Repository& operator=(const Repository& r);
	//ToString
	string toString();
	void load_events();
	void load_from_file();
	void save_to_file();
	void setFileFormat(FileFormat* format);
};
	