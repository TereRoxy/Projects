#pragma once
#include<string>

using namespace std;

//Event class

class Event {
private:
	int peopleNr;
	string title;
	string description;
	string date;
	string time;
	string link;
public:
	//Constructor
	Event() : peopleNr(0), title("NO_TITLE"), description("NO_DESCRIPTION"), date("YYYY-MM-DD"), time("HH:MM"), link("NO_LINK") {}
	Event(int peopleNr, const string& title, const string& description, const string& date, const string& time, const string& link)
		: peopleNr(peopleNr), title(title), description(description), date(date), time(time), link(link) {}
	//Destructor
	~Event() {}
	//Copy constructor
	Event(const Event& other)
		: title(other.title), peopleNr(other.peopleNr), description(other.description),
		date(other.date), time(other.time), link(other.link) {}
	//Getters
	//Get the number of people attending the event
	int getPeopleNr();
	//Get the title of the event
	string getTitle() const;
	//Get the description of the event
	string getDescription() const;
	//Get the date of the event
	string getDate() const;
	//Get the time of the event
	string getTime() const;
	//Get the link to the event website
	string getLink() const;
	//Setters
	//Set the number of people attending the event
	void setPeopleNr(int peopleNr);
	//Set the title of the event
	void setTitle(string title);
	//Set the description of the event
	void setDescription(string description);
	//Set the date of the event
	void setDate(string date);
	//Set the time of the event
	void setTime(string time);
	//Set the link to the event website
	void setLink(string link);
	//Equality operator
	bool operator==(const Event& e);

	Event& operator=(const Event& e);
	//ToString
	string toString();
};
