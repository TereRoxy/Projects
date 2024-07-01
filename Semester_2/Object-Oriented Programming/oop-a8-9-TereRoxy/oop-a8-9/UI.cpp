#include "UI.h"
#include "Validator.h"
#include <iostream>

void UI::printMenu() {

	std::system("CLS");
	while (true)
	{
		printf("Life after school\n");
		printf("1. Admin Mode\n");
		printf("2. User Mode\n");
		printf("0. Exit\n");

		int option;
		printf("Choose an option: ");
		if (cin >> option)
		{
			switch (option)
			{
			case 1:
				printAdminMenu();
				break;
			case 2:

				selectUserListFileType();
				printUserMenu();
				break;
			case 0:
				return;
			default:
				printf("Invalid option\n");
				break;
			}
		}
		else
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input. Please enter a valid integer." << std::endl;
		}
	}
		
}

void UI::printAdminMenu() {
	std::system("CLS");
	while (true)
	{
		printf("\nAdmin Mode\n");
		printf("1. Add an event\n");
		printf("2. Update an event\n");
		printf("3. Delete an event\n");
		printf("4. Get the events\n");
		printf("0. Back\n");

		int option;
		printf("Choose an option: ");
		if (cin >> option)
		{
			switch (option)
			{
			case 1:
				addEventUI();
				break;
			case 2:
				updateEventUI();
				break;
			case 3:
				deleteEventUI();
				break;
			case 4:
				getEventsUI();
				break;
			case 0:
				return;
			default:
				printf("Invalid option\n");
				break;
			}
		}
		else
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input. Please enter a valid integer." << std::endl;
		}
	}
}

void UI::printUserMenu() {
	std::system("CLS");
	while (true)
	{
		printf("\nUser Mode\n");
		printf("1. See all the events in a given month \n");
		printf("2. Delete an event from my list\n");
		printf("3. See the list of events I'm interested in \n");
		printf("4. Open the list of events I'm going to attend\n");
		printf("0. Back\n");

		int option;
		printf("Choose an option: ");
		if (cin >> option)
		{
			switch (option)
			{
			case 1:
				int month;
				printf("Please enter month number: ");
				cin >> month;
				if (month < 1 || month > 12)
					printf("Invalid month.\n");
				seeEventsUserUI(month);
				break;
			case 2:
				deleteEventUserUI();
				break;
			case 3:
				getUserEventsUI();
				break;
			case 4:
				service.saveUserList(filetype);
				openUserList();
				break;
			case 0:
				return;
			default:
				printf("Invalid option\n");
				break;
			}
		}
		else
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input. Please enter a valid integer." << std::endl;
		}
	}
}

void UI::run()
{
	printMenu();
}

void UI::addEventUI()
{
	cin.get();
	printf("Add an event\n");
	printf("Title: ");
	string title;
	getline(cin, title);
	printf("Description: ");
	string description;
	getline(cin, description);
	printf("Date (format YYYY-MM-DD): ");
	string date;
	getline(cin, date);
	
	printf("Time (HH:MM): ");
	string time;
	getline(cin, time);

	printf("Link: ");
	string link;
	getline(cin, link);
	
	printf("Number of people: ");
	int numberOfPeople;
	if (cin >> numberOfPeople)
	{
		EventValidator ev;
		try {
			ev.validateEvent(title, description, date, time, link, numberOfPeople);
		}
		catch (ValidationException& ex)
		{
			printf(ex.what());
			return;
		}

		try {
			service.addEvent(title, description, date, time, link, numberOfPeople);
			printf("Event added successfully!\n");
		}
		catch (RepositoryException& ex)
		{
			printf(ex.what());
			return;
		}
	}
	else
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input. Please enter a valid integer." << std::endl;
	}
}

void UI::updateEventUI()
{
	cin.get();
	printf("Update an event with a given ttile\n");
	printf("Title: ");
	string title;
	getline(cin, title);
	printf("Description: ");
	string description;
	getline(cin, description);
	printf("Date (format YYYY-MM-DD): ");
	string date;
	getline(cin, date);
	
	printf("Time (HH:MM): ");
	string time;
	getline(cin, time);
	
	printf("Link: ");
	string link;
	getline(cin, link);

	printf("Number of people: ");
	int numberOfPeople;
	if (cin >> numberOfPeople)
	{
		EventValidator ev;
		
		try {
			ev.validateEvent(title, description, date, time, link, numberOfPeople);
		}
		catch (ValidationException& ex)
		{
			printf(ex.what());
			return;
		}

		try {
			service.updateEvent(title, description, date, time, link, numberOfPeople);
			printf("Event updated successfully\n");
		}
		catch (RepositoryException& ex) {
			printf(ex.what());
		}
	}
	else
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input. Please enter a valid integer.\n" << std::endl;
	}
}

void UI::deleteEventUI()
{
	cin.get();
	printf("Delete an event with a given title\n");
	printf("Title: ");
	string title;
	getline(cin, title);

	try {
		service.deleteEvent(title);
		printf("Event deleted successfully\n");
	}
	catch (RepositoryException& ex)
	{
		printf(ex.what());
		return;
	}
}

void UI::deleteEventUserUI()
{
	cin.get();
	printf("Please enter the title of the event you want to remove from your watchlist: \n");
	printf(">>> ");
	string title;
	getline(cin, title);
	Event e = {0, title, "", "", "", ""};

	try {
		service.deleteUserEvent(e);
		printf("Event removed successfully\n");
	}
	catch (RepositoryException& ex)
	{
		printf(ex.what());
		return;
	}
}

void UI::seeEventsUserUI(int month)
{
	Service serv = service;
	bool ok = true;
	while (ok)
	{
		ok = false;
		for (int i = 0; i < serv.getSize(); i++)
		{
			Event e = serv.getEvent(i);
			string date = e.getDate();
			int m = stoi(date.substr(5, 2));

			if (m == month && serv.isUserEvent(e)==-1)
			{
				ok = true;
				std::cout << e.toString() << "\n";
				printf("Choose an option: \n");
				printf("1. Add event to my list\n");
				printf("2. See next event \n");
				printf("0. Back\n");
				printf(">>> ");

				string link = e.getLink();
				string command = "start " + link;
				std::system(command.c_str());

				int option;
				if (cin >> option)
				{
					if (option == 1)
					{
						try {
							service.addUserEvent(e);
							printf("Event added successfully! \n");
						}
						catch (RepositoryException& ex)
						{
							printf("Oops! Something went wrong.\n");
						}
					}
					else if (option == 2)
					{
						continue;
					}
					else if (option == 0)
					{
						ok = false;
						return;
					}
					else
					{
						printf("Invalid option \n");
						i--;
					}
				}
			}
		}
	}
	printf("No more events to show.\n");
}

void UI::getUserEventsUI()
{
	cout << service.toStringUser();
}

void UI::getEventsUI()
{
	cout << service.toString();
}

void UI::openUserList() {
	
	if (filetype == "CSV") {
		std::string command = "start events.csv";
		std::system(command.c_str());
	}
	else if (filetype == "HTML")
	{
		std::string command = "start events.html";
		std::system(command.c_str());
	}
}

void UI::selectUserListFileType()
{
	printf("Please select the type of file you want to store the events you're interested in: \n");
	printf("1. CSV\n");
	printf("2. HTML\n");
	printf(">>> ");
	int option;
	cin >> option;
	if (option == 1)
	{
		filetype = "CSV";
	}
	else if (option == 2)
	{
		filetype = "HTML";
	}
	else
	{
		printf("Invalid option\n");
	}
}