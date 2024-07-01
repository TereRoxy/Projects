import unittest
from src.services.services import *
from src.repository.repository import *
from src.domain.domain import *


class ServiceTests(unittest.TestCase):
    def setUp(self):
        self.__repo = MemoryRepo()
        self.__manager = Manager(self.__repo)
        self.__statistics = Statistics(self.__repo)

    def test_add_person(self):
        self.__manager.add_person(1, "John", "0740123456")
        self.assertEqual(len(self.__repo.get_persons()), 1)
        self.assertRaises(Exception, self.__manager.add_person, 1, "John", "0740123456")

    def test_remove_person(self):
        self.__manager.add_person(1, "John", "0740123456")
        self.__manager.remove_person(1)
        self.assertEqual(len(self.__repo.get_persons()), 0)
        self.assertRaises(Exception, self.__manager.remove_person, 1)

    def test_update_person(self):
        self.__manager.add_person(1, "John", "0740123456")
        self.__manager.update_person(1, "John", "0740123457")
        self.assertEqual(self.__repo.get_persons()[0].get_phone(), "0740123457")
        self.assertRaises(Exception, self.__manager.update_person, 2, "John", "0740123457")

    def test_add_activity(self):
        self.__manager.add_activity(1, "12:00", "12.12.2012", "description")
        self.assertEqual(len(self.__repo.get_activities()), 1)
        self.assertRaises(Exception, self.__manager.add_activity, 1, "12:00", "12.12.2012", "description")

    def test_remove_activity(self):
        self.__manager.add_activity(1, "12:00", "12.12.2012", "description")
        self.__manager.remove_activity(1)
        self.assertEqual(len(self.__repo.get_activities()), 0)
        self.assertRaises(Exception, self.__manager.remove_activity, 1)

    def test_update_activity(self):
        self.__manager.add_activity(1, "12:00", "12.12.2012", "description")
        self.__manager.update_activity(1, "13:00", "12.12.2012", "description")
        self.assertEqual(self.__repo.get_activities()[0].get_time(), "13:00")
        self.assertRaises(Exception, self.__manager.update_activity, 2, "13:00", "12.12.2012", "description")

    def test_assign_activity(self):
        self.__manager.add_person(1, "John", "0740123456")
        self.__manager.add_activity(1, "12:00", "12.12.2012", "description")
        self.__manager.assign_activity(1, 1)
        self.assertEqual(len(self.__repo.get_activities()[0].get_person_id()), 1)
        self.assertRaises(Exception, self.__manager.assign_activity, 2, 1)
        self.assertRaises(Exception, self.__manager.assign_activity, 1, 2)

    def test_search_persons(self):
        self.__manager.add_person(1, "Riley", "0740123456")
        self.__manager.add_person(2, "Sam", "0740123457")
        returned_persons = self.__manager.search_persons("Sam", "name")
        self.assertEqual(len(returned_persons), 1)
        returned_persons = self.__manager.search_persons("0740", "phone")
        self.assertEqual(len(returned_persons), 2)
        self.assertRaises(Exception, self.__manager.search_persons, "John", "phone")

    def test_search_activities(self):
        self.__manager.add_activity(1, "12:00", "12.12.2012", "description")
        self.__manager.add_activity(2, "13:00", "13.12.2012", "description2")
        self.assertEqual(len(self.__manager.search_activities("12", "time")), 1)
        self.assertEqual(len(self.__manager.search_activities("12.12", "date")), 1)
        self.assertEqual(len(self.__manager.search_activities("description", "description")), 2)
        self.assertRaises(Exception, self.__manager.search_activities, "metal", "description")

    def test_list_persons(self):
        self.assertEqual(len(self.__manager.list_persons()), 0)
        self.__manager.add_person(1, "John", "0740123456")
        self.assertEqual(len(self.__manager.list_persons()), 1)

    def test_list_activities(self):
        self.assertEqual(len(self.__manager.list_activities()), 0)
        self.__manager.add_activity(1, "12:00", "12.12.2012", "description")
        self.assertEqual(len(self.__manager.list_activities()), 1)


class StatisticsTest(unittest.TestCase):
    def test_get_activities_by_day(self):
        self.__repo = MemoryRepo()
        self.__manager = Manager(self.__repo)
        self.__statistics = Statistics(self.__repo)
        self.__manager.add_activity(1, "12:00", "12.12.2012", "description")
        self.__manager.add_activity(2, "13:00", "12.12.2012", "description2")
        activities = self.__statistics.get_activities_by_day("12.12.2012")
        self.assertEqual(len(activities), 2)
        self.assertRaises(Exception, self.__statistics.get_activities_by_day, "13.12.2012")

    def test_get_activities_by_person(self):
        self.__repo = MemoryRepo()
        self.__manager = Manager(self.__repo)
        self.__statistics = Statistics(self.__repo)
        self.__manager.add_person(1, "John", "0740123456")
        self.__manager.add_activity(1, "12:00", "12.12.2012", "description")
        self.__manager.add_activity(2, "13:00", "12.12.2012", "description2")
        self.__manager.assign_activity(1, 1)
        activities = self.__statistics.get_activities_by_person(1)
        self.assertEqual(len(activities), 1)
        self.assertRaises(Exception, self.__statistics.get_activities_by_person, 2)

    def test_get_busiest_days(self):
        self.__repo = MemoryRepo()
        self.__manager = Manager(self.__repo)
        self.__statistics = Statistics(self.__repo)
        self.__manager.add_activity(1, "12:00", "12.12.2012", "description")
        self.__manager.add_activity(2, "13:00", "12.12.2012", "description2")
        self.__manager.add_activity(3, "12:00", "13.12.2012", "description3")
        self.__manager.add_activity(4, "13:00", "13.12.2012", "description4")
        busiest_days = self.__statistics.get_busiest_days()
        days = []
        for day in busiest_days:
            days.append(day[0])
        self.assertEqual(days, ["12.12.2012", "13.12.2012"])

    def test_sort_activities_by_time(self):
        self.__repo = MemoryRepo()
        self.__manager = Manager(self.__repo)
        self.__statistics = Statistics(self.__repo)
        self.__manager.add_activity(1, "13:00", "12.12.2012", "description")
        self.__manager.add_activity(2, "12:00", "12.12.2012", "description2")
        self.__manager.add_activity(3, "13:00", "13.12.2012", "description3")
        self.__manager.add_activity(4, "12:00", "13.12.2012", "description4")
        self.assertEqual(self.__statistics.sort_activities_by_time(self.__repo.get_activities()),
                         [Activity(2, "12:00", "12.12.2012", "description2"),
                          Activity(4, "12:00", "13.12.2012", "description4"),
                          Activity(1, "13:00", "12.12.2012", "description"),
                          Activity(3, "13:00", "13.12.2012", "description3")])


if __name__ == '__main__':
    unittest.main()
