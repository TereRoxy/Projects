#pragma once

#include "Service.h"

class UI {
private:
	Service& service;
public:
	//Constructor
	UI(Service& s) : service(s) {}
	//Destructor
	~UI() {}
	//Copy constructor
	UI(const UI& other) : service(other.service) {}
	//Add an event to the repository
	void addEventUI();
	//Update an event from the repository
	void updateEventUI();
	//Delete an event from the repository
	void deleteEventUI();
	void deleteEventUserUI();
	//Get the events from the repository
	void getEventsUI();

	void seeEventsUserUI(int month);

	void getUserEventsUI();
	
	//ToString
	//string toString();

	void run();
	
	void printMenu();

	void printAdminMenu();
	
	void printUserMenu();

	//int selectOption();
	
};
