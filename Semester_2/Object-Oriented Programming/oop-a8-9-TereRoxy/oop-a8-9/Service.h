#pragma once

#include "Repository.h"
#include "Exceptions.h"

class MonthEventIterator;

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
	void addEvent(string Title, string Description, string Date, string Time, string Link, int PeopleNr);
	//Update an event from the repository
	void updateEvent(string Title, string Description, string Date, string Time, string Link, int PeopleNr);
	//Delete an event from the repository
	void deleteEvent(string Title);
	//Get the events from the repository
	vector<Event> getEvents();
	//Get the size of the repository
	int getSize();
	//Get the event from the repository by index
	Event getEvent(int index);
	//Get the index of an event from the repository
	int getIndex(string Title);
	//Get the events from the user repository
	//DynamicArray<Event> getUserEvents();
	//Add an event to the user repository and update the number of attending people in the events repository
	void addUserEvent(Event e);

	void deleteUserEvent(Event e);

	int isUserEvent(Event e);

	vector <Event> getEventsByMonth(int mth);
	vector <Event> getUserEvents();

	void saveUserList(std::string fileType);
	void saveAdminList() { eventsRepo.save_to_file(); }

	//void loadUserList();
	
	//ToString
	string toString();

	string toStringUser();

	friend class MonthEventIterator;
	
};

class MonthEventIterator {
private:
	Service& service;
	int month;
	int currentIndex;
	int count;
	// Find the next valid event in the repository
	void findNextValidEvent() {
		count = 0;
		while (count < service.getSize())
		{
			if (currentIndex == service.getSize())
				currentIndex = 0;
			Event currentEvent = service.eventsRepo.getEvent(currentIndex);
			if (stoi(currentEvent.getDate().substr(5, 2)) == month && service.isUserEvent(currentEvent)==-1) {
				return; // Found a valid event
			}
			currentIndex++;
			count++;
		}
		currentIndex = -1; // No valid event found, iterator becomes invalid
	}
public:
	MonthEventIterator(Service& service, int month) : service(service), month(month), currentIndex(0) { findNextValidEvent(); }
	Event getCurrent() const{
		if (valid()) {
			return service.eventsRepo.getEvent(currentIndex);
		}
		else {
			throw exception("Iterator is not valid.");
		};
	}
	bool valid() const{
		return currentIndex < service.getSize() && currentIndex >= 0;
	}
	void next() {
		currentIndex++;
		findNextValidEvent();
	}
	void first() {
		currentIndex = 0;
	}
};