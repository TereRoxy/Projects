#include "Repository.h"

void Repository::addEvent(const Event& e) {
	events.append(e);
}

void Repository::updateEvent(const Event& e, int index) {
	events[index] = e;
}

void Repository::deleteEvent(int index) {
	events.remove(index);
}

DynamicArray<Event> Repository::getEvents() {
	return events;
}

int Repository::getSize() {
	return events.getSize();
}

Event Repository::getEvent(int index) {
	return events[index];
}

int Repository::getIndex(const Event& e) {
	for (int i = 0; i < events.getSize(); ++i) {
		if (events[i].getTitle() == e.getTitle()) {
			return i;
		}
	}
	return -1;
}

//Repository& Repository::operator=(const Repository& r) {
//	events = r.events;
//	return *this;
//}

string Repository::toString() {
	string result;
	for (int i = 0; i < events.getSize(); ++i) {
		result += events[i].toString() + "\n";
	}
	return result;
}

void Repository::load_events()
{
	events.append(Event{ 1, "Title1", "Description1", "2024-08-06", "00:58", "https://toes.sample.edu/" });
	events.append(Event{ 2, "Title2", "Description2", "2024-10-12", "01:10", "https://sample.edu/?army=industry" });
	events.append(Event{ 3, "Title3", "Description3", "2024-10-29", "03:30", "https://www.sample.edu/dinner.aspx" });
	events.append(Event{ 4, "Title4", "Description4", "2024-11-15", "13:05", "http://sample.edu/?squirrel=degree" });
	events.append(Event{ 5, "Title5", "Description5", "2024-11-17", "13:07", "http://sample.org/tiger.html" });
	events.append(Event{ 6, "Title6", "Description6", "2024-11-27", "15:18", "http://www.sample.net/gold?fall=metal" });
	events.append(Event{ 7, "Title7", "Description7", "2024-12-01", "15:32", "http://sample.com/" });
	events.append(Event{ 8, "Title8", "Description8", "2024-12-14", "16:55", "https://sample.info/#flight" });
	events.append(Event{ 9, "Title9", "Description9", "2024-12-24", "17:48", "https://mass.sample.net/" });
	events.append(Event{ 10, "Title10", "Description10", "2024-12-28", "20:59", "https://www.sample.org/#basket" });
}