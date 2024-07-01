from src.domain.domain import Person, Activity
import pickle


class RepositoryException(Exception):
    def __init__(self, message):
        self.__message = message


class MemoryRepo:
    def __init__(self):
        self.__persons = []
        self.__activities = []

    def get_persons(self):
        return self.__persons

    def get_activities(self):
        return self.__activities

    def save_file(self):
        pass

    def get_activity_by_id(self, activity_id):
        for activity in self.__activities:
            if activity.get_activity_id() == activity_id:
                return activity
        raise RepositoryException("Activity not found!")

    def get_person_by_id(self, person_id):
        for person in self.__persons:
            if person.get_person_id() == person_id:
                return person
        raise RepositoryException("Person not found!")

    def add_person(self, person: Person):
        """
        Adds a person to the repository
        :param person:
        :return:
        """
        for p in self.__persons:
            if p.get_person_id() == person.get_person_id():
                raise RepositoryException("Person already exists!")
        self.__persons.append(person)


    def remove_person(self, person_id):
        """
        Removes a person with a specified id from the repository
        :param person_id:
        :return:
        """
        ok = False
        for person in self.__persons:
            if person.get_person_id() == person_id:
                self.__persons.remove(person)
                ok = True
        for activity in self.__activities:
            if person_id in activity.get_person_id():
                activity.remove_person_id(person_id)

        if not ok:
            raise RepositoryException("Person not found!")

    def update_person(self, person_id, new_name, new_phone):
        """
        Updates a person with a specified id from the repository
        :param person_id:
        :param new_name:
        :param new_phone:
        :return:
        """
        for person in self.__persons:
            if person.get_person_id() == person_id:
                person.set_name(new_name)
                person.set_phone(new_phone)
                return person
        raise RepositoryException("Person not found!")

    def add_activity(self, activity: Activity):
        """
        Adds an activity to the repository
        :param activity:
        :return:
        """
        for act in self.__activities:
            if act.get_activity_id() == activity.get_activity_id():
                raise RepositoryException("Activity already exists!")
            if act.get_time() == activity.get_time() and act.get_date() == activity.get_date():
                raise RepositoryException("Two activities cannot take place at the same time!")
        self.__activities.append(activity)

    def remove_activity(self, activity_id):
        """
        Removes an activity with a specified id from the repository
        :param activity_id:
        :return:
        """
        for activity in self.__activities:
            if activity.get_activity_id() == activity_id:
                self.__activities.remove(activity)
                return
        raise RepositoryException("Activity not found!")

    def update_activity(self, activity_id, new_time, new_date, new_description):
        """
        Updates an activity with a specified id from the repository
        :param activity_id:
        :param new_time:
        :param new_date:
        :param new_description:
        :return:
        """
        for activity in self.__activities:
            if activity.get_activity_id() == activity_id:
                activity.set_time(new_time)
                activity.set_date(new_date)
                activity.set_description(new_description)
                return activity
        raise RepositoryException("Activity not found!")

    def assign_activity(self, activity_id, person_id):
        """
        Assigns an activity to a person
        :param activity_id:
        :param person_id:
        :return:
        """
        persons = self.__persons
        for person in persons:
            if person.get_person_id() == person_id:
                break
        else:
            raise RepositoryException("Person not found!")

        for activity in self.__activities:
            if activity.get_activity_id() == activity_id:
                activity.add_person_id(person_id)
                return
        raise RepositoryException("Activity not found!")

    def unassign_activity(self, activity_id, person_id):
        for activity in self.__activities:
            if activity.get_activity_id() == activity_id:
                activity.remove_person_id(person_id)
                self.save_file()
                return
        raise RepositoryException("Activity not found!")

    def reassign_activities(self, activities, person_id):
        if len(activities) != 0:
            for activity in activities:
                self.assign_activity(activity.get_activity_id(), person_id)

    def restore_person(self, person, activities):
        self.add_person(person)
        self.reassign_activities(activities, person.get_person_id())


class FileRepo(MemoryRepo):
    def __init__(self, persons, activities):
        super().__init__()
        self.__persons = persons
        self.__activities = activities
        self.__load_file()

    def __load_file(self):
        try:
            pers = open(self.__persons, "r")
            line = pers.readline().strip()
            while line != "":
                parts = line.split(";")
                person = Person(parts[0], parts[1], parts[2])
                super().add_person(person)
                line = pers.readline().strip()
            pers.close()

            act = open(self.__activities, "r")
            line = act.readline().strip()
            while line != "":
                parts = line.split(";")
                activity = Activity(parts[0], parts[1], parts[2], parts[3])
                super().add_activity(activity)
                line = act.readline().strip()
            act.close()
        except IOError:
            raise RepositoryException("File error!")

    def save_file(self):
        try:
            pers = open(self.__persons, "w")
            for person in super().get_persons():
                pers.write(str(person.get_person_id()) + ";" + person.get_name() + ";" + person.get_phone() + "\n")
            pers.close()

            activities = open(self.__activities, "w")
            for activity in super().get_activities():
                activities.write(str(activity.get_activity_id()) + ";" + activity.get_time() + ";" + activity.get_date() + ";"
                        + activity.get_description() + "\n")
            activities.close()
        except IOError:
            raise RepositoryException("File error!")
        except EOFError:
            persons = []
            activities = []


class PickleRepo(MemoryRepo):
    def __init__(self, persons, activities):
        super().__init__()
        self.__persons = persons
        self.__activities = activities
        self.__load_file()

    def __load_file(self):
        try:
            persons = open(self.__persons, "rb")
            self.__persons = pickle.load(persons)
            activities = open(self.__activities, "rb")
            self.__activities = pickle.load(activities)

            persons.close()
            activities.close()
        except IOError:
            raise RepositoryException("File error!")
        except EOFError:
            persons = []
            activities = []

    def save_file(self):
        try:
            persons = open(self.__persons, "wb")
            pickle.dump(self.__persons, persons)
            activities = open(self.__activities, "wb")
            pickle.dump(self.__activities, activities)

            persons.close()
            activities.close()
        except IOError:
            raise RepositoryException("File error!")
