#include "Service.h"
#include <iostream>
#include <algorithm>

using namespace std;

void Service::addEvent(string Title, string Description, string Date, string Time, string Link, int PeopleNr) {
	Event e{PeopleNr, Title, Description, Date, Time, Link};
	for (int i = 0; i < eventsRepo.getSize(); i++)
		if (eventsRepo.getEvent(i) == e)
			throw RepositoryException("Event with the same title already exists!\n");
	eventsRepo.addEvent(e);
	Event* addedEvent = new Event{ PeopleNr, Title, Description, Date, Time, Link };
	//Create and push add action to the undo stack
	Action* addAction = new ActionAdd(*addedEvent, eventsRepo);
	undoStack.push(addAction);
	//Clear the redo stack
	while (!redoStack.empty())
		redoStack.pop();
}

void Service::updateEvent(string Title, string Description, string Date, string Time, string Link, int PeopleNr) {
	Event e{ PeopleNr, Title, Description, Date, Time, Link };
	int index = eventsRepo.getIndex(e);
	Event oe = eventsRepo.getEvent(index);
	Event* oldEvent = new Event(oe.getPeopleNr(), oe.getTitle(), oe.getDescription(), oe.getDate(), oe.getTime(), oe.getLink());
	eventsRepo.updateEvent(e, index);
	Event* newEvent = new Event{ PeopleNr, Title, Description, Date, Time, Link };
	//Create and push update action to the undo stack
	Action* updateAction = new ActionUpdate(*oldEvent, *newEvent, eventsRepo);

	undoStack.push(updateAction);
	//Clear the redo stack
	while (!redoStack.empty())
		redoStack.pop();
}

void Service::deleteEvent(string Title) {
	Event e{ 0, Title, "", "", "", " " };
	int index = eventsRepo.getIndex(e);
	Event de = eventsRepo.getEvent(index);
	Event* deletedEvent = new Event(de.getPeopleNr(), de.getTitle(), de.getDescription(), de.getDate(), de.getTime(), de.getLink());
	eventsRepo.deleteEvent(index);

	//Create and push remove action to the undo stack
	Action* removeAction = new ActionRemove(*deletedEvent, eventsRepo);
	undoStack.push(removeAction);
	//Clear the redo stack
	while (!redoStack.empty())
		redoStack.pop();
}

void Service::undo() {
	if (undoStack.empty())
		throw RepositoryException("No more undos!\n");

	Action* action = undoStack.top();
	undoStack.pop();
	action->executeUndo();
	//redoStack.push(move(action));
	redoStack.push(action);
}

void Service::redo() {
	if (redoStack.empty())
		throw RepositoryException("No more redos!\n");
	Action* action = redoStack.top();
	redoStack.pop();
	action->executeRedo();
	//undoStack.push(move(action));
	undoStack.push(action);
}

std::vector<Event> Service::getEvents() {
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

void Service::addUserEvent(Event e) {
	for (int i = 0; i < userRepo.getSize(); i++)
		if (userRepo.getEvent(i) == e)
			throw RepositoryException("Event with the same title already exists!\n");
	e.setPeopleNr(e.getPeopleNr() + 1);
	userRepo.addEvent(e);
	
	int index = eventsRepo.getIndex(e);
	eventsRepo.updateEvent(e, index);
}

void Service::deleteUserEvent(Event e) {
	int user_index = userRepo.getIndex(e);
	int index = eventsRepo.getIndex(e);
	userRepo.deleteEvent(user_index);
	e = eventsRepo.getEvent(index);
	e.setPeopleNr(e.getPeopleNr() - 1);
	eventsRepo.updateEvent(e, index);
}

vector <Event> Service::getEventsByMonth(int mth) {
	vector <Event> events = eventsRepo.getEvents();
	vector <Event> result;
	
	// Define a predicate to filter events by month
	auto filterByMonth = [mth](const Event& event) {
		// Assuming the date format is "yyyy.mm.dd"
		// Extract the month part from the date and compare with the given month
		std::string date = event.getDate();
		int eventMonth = std::stoi(date.substr(5, 2)); // Extract month part
		return eventMonth == mth;
	};

	// Use copy_if algorithm to filter events based on the predicate
	std::copy_if(events.begin(), events.end(), std::back_inserter(result), filterByMonth);

	return result;
}

int Service::isUserEvent(Event e) {
	try {
		int index = userRepo.getIndex(e);
		return 1;
	}
	catch (RepositoryException& e) {
		return -1;
	}
}


std::vector<Event> Service::getUserEvents() {
	return userRepo.getEvents();
}

string Service::toString() {
	return eventsRepo.toString();
}

string Service::toStringUser() {
	return userRepo.toString();
}

void Service::saveUserList(std::string fileType) {
	if (fileType == "CSV")
		userRepo.setFileFormat(new CSVFile("events.csv"));
	else if (fileType == "HTML")
		userRepo.setFileFormat(new HTMLFile("events.html"));
	else
		throw RepositoryException("Invalid file format! / File format not chosen\n");
	userRepo.save_to_file();
}