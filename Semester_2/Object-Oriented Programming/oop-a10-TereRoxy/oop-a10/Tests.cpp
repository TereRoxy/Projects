#include <assert.h>
#include <iostream>
#include "Event.h"
#include "Repository.h"
#include "Service.h"

//Event e1 = Event{ 1, "Title11", "Description11", "2024-01-06", "00:58", "https://toes.sample.edu/" };
//Event e2 = Event{ 2, "Title12", "Description12", "2024-02-07", "01:00", "https://toes.sample.edu/" };
//Event e3 = Event{ 3, "Title13", "Description13", "2024-03-08", "02:00", "https://toes.sample.edu/" };
//Event e4 = Event{ 4, "Title14", "Description14", "2024-04-09", "03:00", "https://toes.sample.edu/" };
//Event e5 = Event{ 5, "Title15", "Description15", "2024-05-10", "04:00", "https://toes.sample.edu/" };
//Event e6 = Event{ 6, "Title16", "Description16", "2024-06-11", "05:00", "https://toes.sample.edu/" };
//Event e7 = Event{ 7, "Title17", "Description17", "2024-07-12", "06:00", "https://toes.sample.edu/" };
//Event e8 = Event{ 8, "Title18", "Description18", "2024-08-13", "07:00", "https://toes.sample.edu/" };
//Event e9 = Event{ 9, "Title19", "Description19", "2024-09-14", "08:00", "https://toes.sample.edu/" };
//Event e10 = Event{ 10, "Title20", "Description20", "2024-10-15", "09:00", "https://toes.sample.edu/" };

void testEvent() {
	printf("Testing Event...\n");
	Event e1 = Event{ 1, "Title11", "Description11", "2024-01-06", "00:58", "https://toes.sample.edu/" };
	Event e2 = Event{ 2, "Title12", "Description12", "2024-02-07", "01:00", "https://toes.sample.edu/" };
	assert(e1.getPeopleNr() == 1);
	assert(e1.getTitle() == "Title11");
	assert(e1.getDescription() == "Description11");
	assert(e1.getDate() == "2024-01-06");
	assert(e1.getTime() == "00:58");
	assert(e1.getLink() == "https://toes.sample.edu/");
	e1.setPeopleNr(2);
	e1.setTitle("Title12");
	e1.setDescription("Description12");
	e1.setDate("2024-02-07");
	e1.setTime("01:00");
	e1.setLink("https://toes.sample.edu/");
	assert(e1.getPeopleNr() == 2);
	assert(e1.getTitle() == "Title12");
	assert(e1.getDescription() == "Description12");
	assert(e1.getDate() == "2024-02-07");
	assert(e1.getTime() == "01:00");
	assert(e1.getLink() == "https://toes.sample.edu/");
	assert(e1 == e2);
	e1 = e1;
	Event e15(e1);
	assert(e15 == e1);
	string s = e1.toString();
}

void testRepository()
{
	printf("Testing Repository...\n");

	Event e1 = Event{ 1, "Title11", "Description11", "2024-01-06", "00:58", "https://toes.sample.edu/" };
	Event e2 = Event{ 2, "Title12", "Description12", "2024-02-07", "01:00", "https://toes.sample.edu/" };
	Event e3 = Event{ 3, "Title13", "Description13", "2024-03-08", "02:00", "https://toes.sample.edu/" };
	Event e4 = Event{ 4, "Title14", "Description14", "2024-04-09", "03:00", "https://toes.sample.edu/" };
	Event e5 = Event{ 5, "Title15", "Description15", "2024-05-10", "04:00", "https://toes.sample.edu/" };
	Event e10 = Event{ 10, "Title20", "Description20", "2024-10-15", "09:00", "https://toes.sample.edu/" };
	Repository eventRepo, userRepo;
	
	eventRepo.addEvent(e1);
	eventRepo.addEvent(e2);
	eventRepo.addEvent(e3);
	eventRepo.addEvent(e4);
	eventRepo.addEvent(e5);
	assert(eventRepo.getSize() == 5);
	assert(eventRepo.getEvent(0) == e1);
	
	eventRepo.updateEvent(e1, 0);
	assert(eventRepo.getEvent(0) == e1);


	eventRepo.deleteEvent(0);
	assert(eventRepo.getSize() == 4);
	eventRepo.getEvents();
	string s = eventRepo.toString();
	
	eventRepo.load_events();
}

void testService()
{
	printf("Testing Service...\n");

	Event e1 = Event{ 1, "Title11", "Description11", "2024-01-06", "00:58", "https://toes.sample.edu/" };
	Event e2 = Event{ 2, "Title12", "Description12", "2024-02-07", "01:00", "https://toes.sample.edu/" };
	Event e3 = Event{ 3, "Title13", "Description13", "2024-03-08", "02:00", "https://toes.sample.edu/" };
	Event e4 = Event{ 4, "Title14", "Description14", "2024-04-09", "03:00", "https://toes.sample.edu/" };
	Event e5 = Event{ 5, "Title15", "Description15", "2024-05-10", "04:00", "https://toes.sample.edu/" };
	Event e10 = Event{ 10, "Title20", "Description20", "2024-10-15", "09:00", "https://toes.sample.edu/" };
	Repository eventRepo, userRepo;
	Service service{ eventRepo, userRepo };
	
	service.addEvent("Title11", "Description11", "2024-01-06", "00:58", "https://toes.sample.edu/", 1);
	service.addEvent("Title12", "Description12", "2024-02-07", "01:00", "https://toes.sample.edu/", 2);
	service.addEvent("Title13", "Description13", "2024-03-08", "02:00", "https://toes.sample.edu/", 3);
	service.addEvent("Title14", "Description14", "2024-04-09", "03:00", "https://toes.sample.edu/", 4);
	service.addEvent("Title15", "Description15", "2024-05-10", "04:00", "https://toes.sample.edu/", 5);
	assert(service.getSize() == 5);
	

	service.updateEvent("Title11", "Description20", "2024-10-15", "09:00", "https://toes.sample.edu/", 10);
	
	service.deleteEvent("Title11");
	assert(service.getSize() == 4);
	service.toString();
	service.toStringUser();
	
}

void runAllTests()
{
	printf("Running all tests...\n");
	testEvent();
	testService();
	testRepository();
	printf("All tests passed!\n\n");
}
