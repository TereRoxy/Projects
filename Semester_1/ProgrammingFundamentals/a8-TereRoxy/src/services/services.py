from src.domain.domain import Person, Activity
from src.repository.repository import RepositoryException
import random


class ManagerException(Exception):
    pass


class StatisticsException(Exception):
    pass


class Manager:
    def __init__(self, repo):
        self.__repo = repo

    def add_person(self, person_id, name, phone):
        """
        Adds a person to the repository
        :param person_id: unique id
        :param name:
        :param phone:
        :return:
        """
        person = Person(person_id, name, phone)
        self.__repo.add_person(person)
        return person

    def remove_person(self, person_id):
        """
        Removes a person with a specified id from the repository
        :param person_id:
        :return:
        """
        self.__repo.remove_person(person_id)

    def update_person(self, person_id, new_name, new_phone):
        """
        Updates a person with a specified id from the repository
        :param person_id: unique id
        :param new_name: changes the name of the person
        :param new_phone: changes the phone number of the person
        :return: the new person
        """
        person = self.__repo.update_person(person_id, new_name, new_phone)
        return person

    def add_activity(self, activity_id, time, date, description):
        """
        Adds an activity to the repository
        :param activity_id: unique id
        :param time: hh:mm
        :param date: yyyy-mm-dd
        :param description:
        :return: the added activity
        """
        activity = Activity(activity_id, time, date, description)
        self.__repo.add_activity(activity)
        return activity

    def remove_activity(self, activity_id):
        """
        Removes an activity with a specified id from the repository
        :param activity_id:
        :return:
        """
        self.__repo.remove_activity(activity_id)

    def update_activity(self, activity_id, new_time, new_date, new_description):
        """
        Updates an activity with a specified id from the repository
        :param activity_id:
        :param new_time: changes the time of the activity
        :param new_date: changes the date of the activity
        :param new_description: changes the description of the activity
        :return: the new activity
        """
        new_activity = self.__repo.update_activity(activity_id, new_time, new_date, new_description)
        return new_activity

    def assign_activity(self, activity_id, person_id):
        """
        Assigns an activity to a person
        :param activity_id:
        :param person_id:
        :return:
        """
        self.__repo.assign_activity(activity_id, person_id)

    def search_persons(self, keyword, key):
        persons = self.__repo.get_persons()
        found_persons = []
        for person in persons:
            if key == "name":
                if keyword in (person.get_name() or person.get_name().lower()):
                    found_persons.append(person)
            elif key == "phone":
                if keyword in person.get_phone():
                    found_persons.append(person)
        if len(found_persons) == 0:
            raise ManagerException("No persons found!")
        return found_persons

    def search_activities(self, keyword, key):
        activities = self.__repo.get_activities()
        found_activities = []
        for activity in activities:
            if key == "time":
                if keyword in activity.get_time():
                    found_activities.append(activity)
            elif key == "date":
                if keyword in activity.get_date():
                    found_activities.append(activity)
            elif key == "description":
                if keyword in (activity.get_description() or activity.get_description().lower()):
                    found_activities.append(activity)
        if len(found_activities) == 0:
            raise ManagerException("No activities found!")
        return found_activities

    def list_persons(self):
        return self.__repo.get_persons()

    def list_activities(self):
        return self.__repo.get_activities()


class Statistics:
    def __init__(self, repo):
        self.__repo = repo

    @staticmethod
    def sort_activities_by_time(activities):
        activities.sort(key=lambda activity: activity.get_time())
        return activities

    def get_activities_by_day(self, day):
        activities = self.__repo.get_activities()
        activities_by_day = []
        for activity in activities:
            date = activity.get_date()
            if date == day:
                activities_by_day.append(activity)
        if len(activities_by_day) == 0:
            raise StatisticsException("No activities found in the specified day!")
        activities_by_day = self.sort_activities_by_time(activities_by_day)
        return activities_by_day

    def get_activities_by_person(self, person_id):
        people = self.__repo.get_persons()

        ok = False
        for person in people:
            if person.get_person_id() == person_id:
                ok = True
        if not ok:
            raise RepositoryException("Person not found!")

        activities = self.__repo.get_activities()
        activities_by_person = []
        for activity in activities:
            persons = activity.get_person_id()
            if person_id in persons:
                activities_by_person.append(activity)
        if len(activities_by_person) == 0:
            raise StatisticsException("No activities found for the specified person!")
        activities_by_person = self.sort_activities_by_time(activities_by_person)
        return activities_by_person

    def get_busiest_days(self):
        activities = self.__repo.get_activities()
        days = []
        for activity in activities:
            date = activity.get_date()
            if date not in days:
                days.append(date)
        busiest_days = []
        for day in days:
            activities_by_day = self.get_activities_by_day(day)
            busiest_days.append([day, activities_by_day])

        busiest_days.sort(key=lambda day: len(day[1]), reverse=False)
        return busiest_days


class GenerateActivities:
    def __init__(self, repo):
        times = ["09:00", "10:00", "11:00", "12:00", "13:00", "14:00", "15:00"]
        dates = ["2023-12-09", "2023-12-10", "2023-12-11", "2023-12-12", "2023-12-13", "2023-12-14", "2023-12-15"]
        descriptions = ["Birthday", "Meeting", "Lunch", "Dinner", "Breakfast", "Work", "Course"]
        i = 1
        while i < 21:
            activities = repo.get_activities()
            activity_id = str(i)
            time = random.choice(times)
            date = random.choice(dates)
            description = random.choice(descriptions)
            activity = Activity(activity_id, time, date, description)
            if activity not in activities:
                repo.add_activity(activity)
                i += 1


class GeneratePersons:
    def __init__(self, repo):
        names = ["Christina", "Riley", "Alex", "Atlas", "Nova", "Anna", "Sky", "Andrew",
                 "Meredith", "Sam", "Sara", "Bailey", "Derek", "Mark", "Lexie", "Burke", "Izzy"]
        phones = ["0745123456", "0723456789", "0756654321", "0767123456", "0745654321", "0723456789", "0756123456",
                  "0767987654", "0745123456", "0723987654", "0732456123", "0756832483", "0735275678", "0769132013",
                  "0745531320", "0761073712", "0748188829", "0736604034", "0747651079", "0757095794"]
        ids = ["2810716051236", "6040314122522", "2940314122522", "5010319253122", "1900616319651", "2941030131456",
               "2961102272081", "5000518278990", "1910207059314", "5030124259044", "1", "2", "3", "4", "5", "6", "7",
               "8", "9", "10"]
        i = 0
        while i < 20:
            person_id = ids[i]
            name = random.choice(names)
            phone = random.choice(phones)
            person = Person(person_id, name, phone)
            repo.add_person(person)
            i += 1


class AssignActivities:
    def __init__(self, repo):
        persons = repo.get_persons()
        activities = repo.get_activities()
        for person in persons:
            for activity in activities:
                if random.randint(0, 1) == 1:
                    repo.assign_activity(activity.get_activity_id(), person.get_person_id())
