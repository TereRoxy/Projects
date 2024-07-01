#include "Service.h"
#include <iostream>

int Service::addEvent(string Title, string Description, string Date, string Time, string Link, int PeopleNr) {
	Event e{PeopleNr, Title, Description, Date, Time, Link};
	for (int i = 0; i < eventsRepo.getSize(); i++)
		if (eventsRepo.getEvent(i) == e)
			return -1;
	eventsRepo.addEvent(e);
	return 1;
}

int Service::updateEvent(string Title, string Description, string Date, string Time, string Link, int PeopleNr) {
	Event e{ PeopleNr, Title, Description, Date, Time, Link };
	int index = eventsRepo.getIndex(e);
	if (index == -1)
		return -1;
	eventsRepo.updateEvent(e, index);
	return 1;
}

int Service::deleteEvent(string Title) {
	Event e{ 0, Title, "", "", "", " " };
	int index = eventsRepo.getIndex(e);
	if (index == -1)
		return -1;
	eventsRepo.deleteEvent(index);
	return 1;
}

DynamicArray<Event> Service::getEvents() {
	return eventsRepo.getEvents();
}

int Service::getSize() {
	return eventsRepo.getSize();
}

Event Service::getEvent(int index) {
	return eventsRepo.getEvent(index);
}

int Service::getIndex(string Title) {
	Event e{ 0, Title, "", "", "", "" };
	return eventsRepo.getIndex(e);
}

int Service::addUserEvent(Event e) {
	for (int i = 0; i < userRepo.getSize(); i++)
		if (userRepo.getEvent(i) == e)
			return -1;
	e.setPeopleNr(e.getPeopleNr() + 1);
	userRepo.addEvent(e);
	
	int index = eventsRepo.getIndex(e);
	eventsRepo.updateEvent(e, index);
	return 1;
}

int Service::deleteUserEvent(Event e) {
	int user_index = userRepo.getIndex(e);
	int index = eventsRepo.getIndex(e);
	if (user_index == -1)
		return -1;
	userRepo.deleteEvent(user_index);
	e = eventsRepo.getEvent(index);
	e.setPeopleNr(e.getPeopleNr() - 1);
	eventsRepo.updateEvent(e, index);
	return 1;
}

int Service::isUserEvent(Event e) {
	int index = userRepo.getIndex(e);
	return index;
}

string Service::toString() {
	return eventsRepo.toString();
}

string Service::toStringUser() {
	return userRepo.toString();
}