#include "Event.h"

int Event::getPeopleNr() const {
	return peopleNr;
}

string Event::getTitle() const {
	return title;
}

string Event::getDescription() const {
	return description;
}

string Event::getDate() const {
	return date;
}

string Event::getTime() const {
	return time;
}

string Event::getLink() const {
	return link;
}

void Event::setPeopleNr(int peopleNr) {
	this->peopleNr = peopleNr;
}

void Event::setTitle(string title) {
	this->title = title;
}

void Event::setDescription(string description) {
	this->description = description;
}

void Event::setDate(string date) {
	this->date = date;
}

void Event::setTime(string time) {
	this->time = time;
}

void Event::setLink(string link) {
	this->link = link;
}

Event& Event::operator=(const Event& e) {
	if (this == &e) {
		return *this;
	}
	peopleNr = e.peopleNr;
	title = e.title;
	description = e.description;
	date = e.date;
	time = e.time;
	link = e.link;
	return *this;
}

bool Event::operator==(const Event& e) {
	return title == e.title;
}

string Event::toString() {
	//return to_string(peopleNr) + " " + title + " " + description + " " + date + " " + time + " " + link;
	return "Title: " + title + " | Description: " + description + " | Date: " + date + " | Time: " + time + " | Link: " + link + " | People attending: " + to_string(peopleNr) + "\n";
}