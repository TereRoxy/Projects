from src.domain.domain import Person, Activity
from src.repository.repository import RepositoryException
import random
import src.services.undo_service as undo


class ManagerException(Exception):
    pass


class StatisticsException(Exception):
    pass


class Manager:
    def __init__(self, repo, undo, files=None):
        self.__repo = repo
        self.__undo = undo

    def add_person(self, person_id, name, phone):
        person = Person(person_id, name, phone)
        self.__repo.add_person(person)

        activities = self.get_activities_by_person_id(person_id)
        remove = undo.Command(self.remove_person, person_id)
        add = undo.Command(self.__repo.restore_person, person, activities)
        undo_operation = undo.Operation(remove, add)
        self.__undo.record_for_undo(undo_operation)
        return person

    def remove_person(self, person_id):
        person = self.__repo.get_person_by_id(person_id)
        activities = self.get_activities_by_person_id(person_id)
        self.__repo.remove_person(person_id)

        # print(activities)
        add = undo.Command(self.__repo.restore_person, person, activities)
        remove = undo.Command(self.__repo.remove_person, person_id)
        undo_operation = undo.Operation(add, remove)
        self.__undo.record_for_undo(undo_operation)

    def update_person(self, person_id, new_name, new_phone):
        person = self.__repo.get_person_by_id(person_id)
        person = self.__repo.update_person(person_id, new_name, new_phone)

        old_person = undo.Command(self.__repo.update_person, person_id, person.get_name(), person.get_phone())
        new_person = undo.Command(self.__repo.update_person, person_id, new_name, new_phone)
        undo_operation = undo.Operation(old_person, new_person)
        self.__undo.record_for_undo(undo_operation)
        return person

    def add_activity(self, activity_id, time, date, description):
        activity = Activity(activity_id, time, date, description)
        self.__repo.add_activity(activity)

        remove = undo.Command(self.remove_activity, activity_id)
        add = undo.Command(self.add_activity, activity_id, time, date, description)
        undo_operation = undo.Operation(remove, add)
        self.__undo.record_for_undo(undo_operation)
        return activity

    def remove_activity(self, activity_id):
        activity = self.__repo.get_activity_by_id(activity_id)
        self.__repo.remove_activity(activity_id)

        add = undo.Command(self.__repo.add_activity, activity)
        remove = undo.Command(self.__repo.remove_activity, activity_id)
        undo_operation = undo.Operation(add, remove)
        self.__undo.record_for_undo(undo_operation)

    def update_activity(self, activity_id, new_time, new_date, new_description):
        activity = self.__repo.get_activity_by_id(activity_id)
        self.__repo.update_activity(activity_id, new_time, new_date, new_description)

        old_activity = undo.Command(self.__repo.update_activity, activity_id, activity.get_time(),
                                    activity.get_date(), activity.get_description())
        new_activity = undo.Command(self.__repo.update_activity, activity_id, new_time, new_date, new_description)
        undo_operation = undo.Operation(old_activity, new_activity)
        self.__undo.record_for_undo(undo_operation)
        return new_activity

    def assign_activity(self, activity_id, person_id):
        self.__repo.assign_activity(activity_id, person_id)

        unassign = undo.Command(self.__repo.unassign_activity, activity_id, person_id)
        assign = undo.Command(self.__repo.assign_activity, activity_id, person_id)
        undo_operation = undo.Operation(unassign, assign)
        self.__undo.record_for_undo(undo_operation)

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

    def get_activities_by_person_id(self, person_id):
        activities = self.__repo.get_activities()
        activities_by_person_id = []
        for activity in activities:
            if person_id in activity.get_person_id():
                activities_by_person_id.append(activity)
        return activities_by_person_id

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
        dates = ["2023-12-09", "2023-12-10", "2023-12-11", "2023-12-12", "2023-12-13", "2023-12-14",
                 "2023-12-15", "2023-12-16"]
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
        ids = ["2810716", "6040314", "294031", "5010", "19006", "29410",
               "2961102", "50005", "19102", "503012", "1", "2", "3", "4", "5", "6", "7",
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
