#include "Repository.h"
#include "Exceptions.h"
#include <fstream>

void Repository::addEvent(const Event& e) {
	events.push_back(e);
}

void Repository::updateEvent(const Event& e, int index) {
	events[index] = e;
}

void Repository::deleteEvent(int index) {
	events.erase(events.begin() + index);
}

vector<Event> Repository::getEvents() {
	return events;
}

int Repository::getSize() {
	return events.size();
}

Event Repository::getEvent(int index) {
	return events[index];
}

int Repository::getIndex(const Event& e) {

	for (int i = 0; i < events.size(); i++) {
		if (events[i] == e)
			return i;
	}
	throw RepositoryException("Event not found!");
}

//Repository& Repository::operator=(const Repository& r) {
//	events = r.events;
//	return *this;
//}

string Repository::toString() {
	string result;
	for (auto it : events) {
		result += it.toString() + "\n";
	}
	return result;
}

void Repository::load_events()
{
	events.push_back(Event{ 1, "Title1", "Description1", "2024-08-06", "00:58", "https://toes.sample.edu/" });
	events.push_back(Event{ 2, "Title2", "Description2", "2024-10-12", "01:10", "https://sample.edu/?army=industry" });
	events.push_back(Event{ 3, "Title3", "Description3", "2024-10-29", "03:30", "https://www.sample.edu/dinner.aspx" });
	events.push_back(Event{ 4, "Title4", "Description4", "2024-11-15", "13:05", "http://sample.edu/?squirrel=degree" });
	events.push_back(Event{ 5, "Title5", "Description5", "2024-11-17", "13:07", "http://sample.org/tiger.html" });
	events.push_back(Event{ 6, "Title6", "Description6", "2024-11-27", "15:18", "http://www.sample.net/gold?fall=metal" });
	events.push_back(Event{ 7, "Title7", "Description7", "2024-12-01", "15:32", "http://sample.com/" });
	events.push_back(Event{ 8, "Title8", "Description8", "2024-12-14", "16:55", "https://sample.info/#flight" });
	events.push_back(Event{ 9, "Title9", "Description9", "2024-12-24", "17:48", "https://mass.sample.net/" });
	events.push_back(Event{ 10, "Title10", "Description10", "2024-12-28", "20:59", "https://www.sample.org/#basket" });
}

void Repository::load_from_file()
{	
	events = fileFormat->loadFromFile();
}

void Repository::save_to_file()
{
	fileFormat->saveToFile(events);
}

void Repository::setFileFormat(FileFormat* format)
{
	fileFormat = format;
}