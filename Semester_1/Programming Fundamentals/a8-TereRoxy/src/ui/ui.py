from src.services.services import *
from src.repository.repository import RepositoryException
import texttable as tt
import datetime


class UI:

    def run(self, service: Manager, statistics: Statistics):
        while True:
            UI.print_menu()
            option = input("Choose option: ")
            if option == "1":
                self.option_1(service)

            elif option == "2":
                self.option_2(service)

            elif option == "3":
                self.option_3(service)

            elif option == "4":
                self.option_4(service)
            elif option == "5":
                self.option_5(service)
            elif option == "6":
                self.option_6(service)
            elif option == "7":
                self.option_7(service)
            elif option == "8":
                self.option_8(service)
            elif option == "9":
                self.option_9(service)
            elif option == "10":
                self.option_10(service)
            elif option == "11":
                self.option_11(statistics)
            elif option == "12":
                self.option_12(statistics)
            elif option == "13":
                self.option_13(statistics)
            elif option == "0":
                return
            else:
                print("Invalid option!")

    def option_1(self, service: Manager):
        person_id = input("Person ID: ")
        name = input("Name: ")
        phone = input("Phone: ")
        try:
            person = service.add_person(person_id, name, phone)
            table = self.create_person_table([person])
            print(table)
            print("Person added successfully!")
        except Exception as re:
            print(re)

    @staticmethod
    def option_2(controller: Manager):
        try:
            person_id = input("Person ID: ")
            controller.remove_person(person_id)
            print("Person removed successfully!")
        except Exception as re:
            print(str(re))

    def option_3(self, service: Manager):
        person_id = input("Person ID: ")
        new_name = input("New name: ")
        new_phone = input("New phone: ")
        try:
            new_person = service.update_person(person_id, new_name, new_phone)
            table = self.create_person_table([new_person])
            print(table)
            print("Person updated successfully!")
        except Exception as re:
            print(str(re))

    def option_4(self, controller: Manager):
        result = controller.list_persons()
        table = self.create_person_table(result)
        print(table)

    # TODO search persons by name or phone number
    def option_5(self, controller: Manager):
        print("     Search persons by:")
        print("         1. Name")
        print("         2. Phone number")
        print("     Choose option: ")
        op = input(">> ")
        keyword = input("Search keyword: ")
        if op == "1":
            key = "name"
        elif op == "2":
            key = "phone"
        else:
            print("Invalid option!")
            return
        try:
            found_persons = controller.search_persons(keyword, key)
            result = self.create_person_table(found_persons)
            print(result)
        except Exception as e:
            print(str(e))

    def option_6(self, controller: Manager):
        activity_id = input("Activity ID: ")

        time = input("Time (hh:mm): ")
        if not self.validate_time(time):
            print("Invalid time!")
            return

        date = input("Date (yyyy-mm-dd): ")
        if not self.validate_date(date):
            print("Invalid date!")
            return
        description = input("Description: ")
        try:
            activity = controller.add_activity(activity_id, time, date, description)
            table = self.create_activity_table([activity])
            print(table)
            print("Activity added successfully!")
        except Exception as re:
            print(re)

    @staticmethod
    def option_7(controller: Manager):
        try:
            activity_id = input("Activity ID: ")
            controller.remove_activity(activity_id)
            print("Activity removed successfully!")
        except Exception as re:
            print(re)

    def option_8(self, controller: Manager):
        self.print_submenu_update_activity()
        op = input("Choose option: ")
        if op == "1":
            activity_id = input("Activity ID: ")

            new_time = input("New time (hh:mm): ")
            if not self.validate_time(new_time):
                print("Invalid time!")
                return

            new_date = input("New date (yyyy-mm-dd): ")
            if not self.validate_date(new_date):
                print("Invalid date!")
                return
            new_description = input("New description: ")
            try:
                new_activity = controller.update_activity(activity_id, new_time, new_date, new_description)
                table = self.create_activity_table([new_activity])
                print(table)
                print("Activity updated successfully!")
            except Exception as re:
                print(re)

        elif op == "2":
            activity_id = input("Activity ID: ")
            person_id = input("Person ID: ")
            try:
                controller.assign_activity(activity_id, person_id)
                print("Activity assigned successfully!")
            except Exception as re:
                print(re)
        else:
            print("Invalid option!")

    def option_9(self, controller: Manager):
        result = controller.list_activities()
        table = self.create_activity_table(result)
        print(table)

    # TODO search activities by date/time or description
    def option_10(self, controller: Manager):
        print("     Search activities by:")
        print("         1. Time (hh:mm) ")
        print("         2. Date (yyyy-mm-dd) ")
        print("         3. Description")
        print("     Choose option: ")
        op = input(">> ")
        keyword = input("Search keyword: ")
        if op == "1":
            key = "time"
            if not self.validate_time(keyword):
                print("Invalid time!")
                return
        elif op == "2":
            key = "date"
            if not self.validate_date(keyword):
                print("Invalid date!")
                return
        elif op == "3":
            key = "description"
        else:
            print("Invalid option!")
            return
        try:
            found_activities = controller.search_activities(keyword, key)
            result = self.create_activity_table(found_activities)
            print(result)
        except Exception as me:
            print(me)

    # TODO statistics
    def option_11(self, controller: Statistics):
        print("     Please enter a date in the following format: yyyy-mm-dd")
        date = input(">> ")
        if not self.validate_date(date):
            print("Invalid date!")
            return
        try:
            result = controller.get_activities_by_day(date)
            table = self.create_activity_table(result)
            print(table)
        except Exception as ex:
            print(ex)

    def option_12(self, controller: Statistics):
        person_id = input("Person ID: ")
        try:
            result = controller.get_activities_by_person(person_id)
            table = self.create_activity_table(result)
            print(table)
        except Exception as ex:
            print(ex)

    def option_13(self, controller: Statistics):
        result = controller.get_busiest_days()
        # table = self.create_activity_table(result)
        # print(table)
        dates = []
        for day in result:
            dates.append(day[0])
        print(dates)

    @staticmethod
    def create_activity_table(activities):
        table = tt.Texttable()
        table.header(["Activity ID", "Time", "Date", "Description", "Persons"])
        for activity in activities:
            table.add_row([activity.get_activity_id(), activity.get_time(), activity.get_date(),
                           activity.get_description(), activity.get_person_id()])
        return table.draw()

    @staticmethod
    def create_person_table(persons):
        table = tt.Texttable()
        table.header(["Person ID", "Name", "Phone"])
        for person in persons:
            ssn = str(person.get_person_id())
            phone = str(person.get_phone())
            table.add_row([ssn, person.get_name(), phone])
        return table.draw()

    @staticmethod
    def validate_date(date):
        try:
            datetime.datetime.strptime(date, '%Y-%m-%d')
            return True
        except ValueError:
            return False

    @staticmethod
    def validate_time(time):
        try:
            datetime.datetime.strptime(time, '%H:%M')
            return True
        except ValueError:
            return False

    @staticmethod
    def print_menu():
        print("MANAGE PERSONS")
        print("1. Add person")
        print("2. Remove person")
        print("3. Update person")
        print("4. List persons")
        print("5. Search persons")
        print("\n")
        print("MANAGE ACTIVITIES")
        print("6. Add activity")
        print("7. Remove activity")
        print("8. Update activity")
        print("9. List activities")
        print("10. Search activities")
        print("\n")
        print("STATISTICS")
        print("11. Activities on a given day")
        print("12. Activities for a given person")
        print("13. Busiest days")
        print("\n 0. EXIT")

    @staticmethod
    def print_submenu_update_activity():
        print("     1. Edit activity information")
        print("     2. Assign activity to a person")
