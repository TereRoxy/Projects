from src.domain.domain import Person, Activity


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
        for person in self.__persons:
            if person.get_person_id() == person_id:
                self.__persons.remove(person)
                return
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
