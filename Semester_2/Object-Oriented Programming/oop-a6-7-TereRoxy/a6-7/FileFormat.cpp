#include "FileFormat.h"

void CSVFile::saveToFile(const std::vector<Event>& events){
	std::ofstream file(filename);
	for (const auto& event : events) {
		file << event.getPeopleNr() << "," << event.getTitle() << "," << event.getDescription() << "," << event.getDate() << "," << event.getTime() << "," << event.getLink() << "\n";
	}
	file.close();
}

std::vector<Event> CSVFile::loadFromFile() {
	ifstream file(filename);
    std::vector<Event>events;
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return events;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        int peopleNr;
        string title, description, date, time, link;

        // Read data from CSV line
        getline(ss, title, ',');
        getline(ss, description, ',');
        getline(ss, date, ',');
        getline(ss, time, ',');
        getline(ss, link, ',');
        ss >> peopleNr; // Assuming peopleNr is the last field

        // Construct Event object and add to vector
        events.push_back(Event(peopleNr, title, description, date, time, link));
    }

    file.close();
	return events;
}

void HTMLFile::saveToFile(const std::vector<Event>& events) {
	std::ofstream file(filename);
	file << "<!DOCTYPE html>\n<html>\n<head>\n<title>Events</title>\n</head>\n<body>\n<table border=\"1\">\n<tr>\n<th>PeopleNr</th>\n<th>Title</th>\n<th>Description</th>\n<th>Date</th>\n<th>Time</th>\n<th>Link</th>\n</tr>\n";
	for (const auto& event : events) {
		file << "<tr>\n<td>" << event.getPeopleNr() << "</td>\n<td>" << event.getTitle() << "</td>\n<td>" << event.getDescription() << "</td>\n<td>" << event.getDate() << "</td>\n<td>" << event.getTime() << "</td>\n<td>" << event.getLink() << "</td>\n</tr>\n";
	}
	file << "</table>\n</body>\n</html>";
	file.close();
}

std::vector<Event> HTMLFile::loadFromFile() {
	std::ifstream file(filename);
	std::vector<Event> events;
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return events;
    }

    string line;
    bool inTable = false;
    while (getline(file, line)) {
        // Check if inside the table
        if (line.find("<table") != string::npos) {
            inTable = true;
            continue; // Skip table header
        }
        if (line.find("</table") != string::npos) {
            break; // End of table
        }

        // Parse table row
        if (inTable && line.find("<tr>") != string::npos) {
            Event event;
            getline(file, line); // Read next line (should contain event data)
            stringstream ss(line);
            string token;
            int index = 0;
            while (getline(ss, token, '>')) {
                if (index == 1) // PeopleNr
                    event.setPeopleNr(stoi(token));
                else if (index == 3) // Title
                    event.setTitle(token);
                else if (index == 5) // Description
                    event.setDescription(token);
                else if (index == 7) // Date
                    event.setDate(token);
                else if (index == 9) // Time
                    event.setTime(token);
                else if (index == 11) // Link
                    event.setLink(token);
                index++;
            }
            events.push_back(event);
        }
    }

    file.close();
    return events;
}

void TextFile::saveToFile(const std::vector<Event>& events) {
	std::ofstream file(filename);
	for (const auto& event : events) {
		file << event;
	}
	file.close();
}

std::vector<Event> TextFile::loadFromFile() {
	std::ifstream file(filename);
	std::vector<Event> events;
	Event e;
	while (file >> e) {
		events.push_back(e);
	}
	return events;
}