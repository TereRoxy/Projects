#include "UI.h"
#include <iostream>

int validate_time(string time);
int validate_date(string date);
int validate_link(string link);

void UI::printMenu() {

	system("CLS");
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
	system("CLS");
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
	system("CLS");
	while (true)
	{
		printf("\nUser Mode\n");
		printf("1. See all the events in a given month \n");
		printf("2. Delete an event from my list\n");
		printf("3. See the list of events I'm interested in \n");
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
	//Validate date
	if (validate_date(date) == 0)
		return;
	
	printf("Time (HH:MM): ");
	string time;
	getline(cin, time);
	//Validate time
	if (time.length() != 5 || time[2] != ':')
	{
		printf("Invalid time format\n");
		return;
	}
	
	printf("Link: ");
	string link;
	getline(cin, link);

	if (validate_link(link) == 0)
		return;
	
	printf("Number of people: ");
	int numberOfPeople;
	if (cin >> numberOfPeople)
	{
		if (service.addEvent(title, description, date, time, link, numberOfPeople) == 1)
			printf("Event added successfully\n");
		else
			printf("Event with the same title already exists\n");
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
	//Validate date
	if (validate_date(date) == 0)
		return;
	printf("Time (HH:MM): ");
	string time;
	getline(cin, time);
	//Validate time
	if (validate_time(time)==0)
		return;
	printf("Link: ");
	string link;
	getline(cin, link);

	if (validate_link(link) == 0)
		return;
	
	printf("Number of people: ");
	int numberOfPeople;
	if (cin >> numberOfPeople)
	{
		if (numberOfPeople < 0)
		{
			printf("Invalid number of people\n");
			return;
		}
		if (service.updateEvent(title, description, date, time, link, numberOfPeople) == 1)
			printf("Event updated successfully\n");
		else
			printf("Event not found\n");
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
	if (service.deleteEvent(title) == 1)
		printf("Event deleted successfully\n");
	else
		printf("Event not found\n");
}

void UI::deleteEventUserUI()
{
	cin.get();
	printf("Please enter the title of the event you want to remove from your watchlist: \n");
	printf(">>> ");
	string title;
	getline(cin, title);
	Event e = {0, title, "", "", "", ""};
	if (service.deleteUserEvent(e) == 1)
	{
		printf("Event removed successfully\n");
	}
	else
	{
		printf("Event not found\n");
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
				system(command.c_str());

				int option;
				if (cin >> option)
				{
					if (option == 1)
					{
						if (serv.addUserEvent(e) == 1)
							printf("Event added successfully! \n");
						else
							printf("Oops! Something went wrong. \n");
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

int validate_date(string date)
{
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
	{
		printf("Invalid date format\n");
		return 0;
	}
	int year = stoi(date.substr(0, 4));
	int month = stoi(date.substr(5, 2));
	int day = stoi(date.substr(8, 2));
	if (month < 1 || month > 12)
	{
		printf("Invalid month\n");
		return 0;
	}
	if (day < 1 || day > 31)
	{
		printf("Invalid day\n");
		return 0;
	}
	if (month == 2)
	{
		if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
		{
			if (day > 29)
			{
				printf("Invalid day\n");
				return 0;
			}
		}
		else
		{
			if (day > 28)
			{
				printf("Invalid day\n");
				return 0;
			}
		}
	}
	if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		if (day > 30)
		{
			printf("Invalid day\n");
			return 0;
		}
	}
	return 1;
}

int validate_time(string time)
{
	if (time.length() != 5 || time[2] != ':')
	{
		printf("Invalid time format\n");
		return 0;
	}
	int hour = stoi(time.substr(0, 2));
	int minute = stoi(time.substr(3, 2));
	if (hour < 0 || hour > 23)
	{
		printf("Invalid hour\n");
		return 0;
	}
	if (minute < 0 || minute > 59)
	{
		printf("Invalid minute\n");
		return 0;
	}
	return 1;
}

int validate_link(string link)
{
	if (link.length() == 0)
	{
		printf("Invalid link\n");
		return 0;
	}
	return 1;
}