#pragma once

#include "Repository.h"

class Service {
private:
	Repository& eventsRepo;
	Repository& userRepo;
public:
	//Constructor
	Service(Repository& erepo, Repository& urepo) : eventsRepo(erepo), userRepo(urepo) {}
	//Destructor
	~Service() {}
	//Copy constructor
	//Service(const Service& other) : eventsRepo(other.eventsRepo), userRepo(other.userRepo) {}
	//Add an event to the repository
	int addEvent(string Title, string Description, string Date, string Time, string Link, int PeopleNr);
	//Update an event from the repository
	int updateEvent(string Title, string Description, string Date, string Time, string Link, int PeopleNr);
	//Delete an event from the repository
	int deleteEvent(string Title);
	//Get the events from the repository
	DynamicArray<Event> getEvents();
	//Get the size of the repository
	int getSize();
	//Get the event from the repository by index
	Event getEvent(int index);
	//Get the index of an event from the repository
	int getIndex(string Title);
	//Get the events from the user repository
	//DynamicArray<Event> getUserEvents();
	//Add an event to the user repository and update the number of attending people in the events repository
	int addUserEvent(Event e);

	int deleteUserEvent(Event e);

	int isUserEvent(Event e);
	
	//ToString
	string toString();

	string toStringUser();
};