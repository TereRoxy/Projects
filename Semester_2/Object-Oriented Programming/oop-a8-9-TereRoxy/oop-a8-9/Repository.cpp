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
	events.push_back(Event{ 1, "Title1", "Description1", "2024-08-06", "00:58", "https://open.spotify.com/track/6ErpU9kpyXJx4QxrrCDPRd?si=ed7a5cc621a04acf" });
	events.push_back(Event{ 2, "Title2", "Description2", "2024-10-12", "01:10", "https://open.spotify.com/track/7g3htkaLz4ETFn0cifwM3y?si=fe6bb9b5b4f54307" });
	events.push_back(Event{ 3, "Title3", "Description3", "2024-10-29", "03:30", "https://open.spotify.com/track/7iv32XEy2HlM7PqQO4lp5f?si=63cae3bd81b34061" });
	events.push_back(Event{ 4, "Title4", "Description4", "2024-11-15", "13:05", "https://open.spotify.com/track/5Z0UnEtpLDQyYlWwgi8m9C?si=c327086348694bc5" });
	events.push_back(Event{ 5, "Title5", "Description5", "2024-11-17", "13:07", "https://open.spotify.com/track/0AjOYUUlXUB6PWVQO1S1Cr?si=2b36d2c212604c7b" });
	events.push_back(Event{ 6, "Title6", "Description6", "2024-11-27", "15:18", "https://open.spotify.com/track/4UzVcXufOhGUwF56HT7b8M?si=b4b820441c8448c0" });
	events.push_back(Event{ 7, "Title7", "Description7", "2024-12-01", "15:32", "https://open.spotify.com/track/0BxE4FqsDD1Ot4YuBXwAPp?si=a79507a07e4045b4" });
	events.push_back(Event{ 8, "Title8", "Description8", "2024-12-14", "16:55", "https://open.spotify.com/track/4Ai0ANRDYwx6mCD4Uty1WS?si=86588117e72e467f" });
	events.push_back(Event{ 9, "Title9", "Description9", "2024-12-24", "17:48", "https://open.spotify.com/track/3I5azi0831uNpYQsfYsW7G?si=9a86d481c97343dc" });
	events.push_back(Event{ 10, "Title10", "Description10", "2024-12-28", "20:59", "https://open.spotify.com/track/44Xyja7xYPlVC6v2CeweSi?si=c895ede742184299" });
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