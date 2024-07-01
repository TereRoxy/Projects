class Person:
    def __init__(self, person_id, name, phone):
        self.__name = name
        self.__person_id = person_id
        self.__phone = phone

    def get_name(self):
        return self.__name

    def get_person_id(self):
        return self.__person_id

    def get_phone(self):
        return self.__phone

    def set_name(self, name):
        self.__name = name

    def set_phone(self, phone):
        self.__phone = phone

    def set_person_id(self, person_id):
        self.__person_id = person_id


class Activity:
    def __init__(self, activity_id, time, date, description):
        self.__activity_id = activity_id
        self.__person_id = []
        self.__date = date
        self.__time = time
        self.__description = description

    def __eq__(self, other):
        if self.__activity_id == other.__activity_id or (self.__time == other.__time and self.__date == other.__date):
            return True
        return False

    def get_activity_id(self):
        return self.__activity_id

    def get_person_id(self):
        return self.__person_id

    def get_description(self):
        return self.__description

    def get_date(self):
        return self.__date

    def get_time(self):
        return self.__time

    def set_activity_id(self, activity_id):
        self.__activity_id = activity_id

    def set_person_id(self, person_id):
        self.__person_id = person_id

    def add_person_id(self, person_id):
        self.__person_id.append(person_id)

    def remove_person_id(self, person_id):
        self.__person_id.remove(person_id)

    def set_date(self, date):
        self.__date = date

    def set_time(self, time):
        self.__time = time

    def set_description(self, description):
        self.__description = description