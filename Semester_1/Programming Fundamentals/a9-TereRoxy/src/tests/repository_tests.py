import unittest
from src.repository.repository import *
from src.domain.domain import Person, Activity


class RepoTest(unittest.TestCase):
    def setUp(self):
        self.__repo = MemoryRepo()
        self.__repo.add_person(Person(1, "John", "123"))
        self.__repo.add_person(Person(2, "Mary", "456"))
        self.__repo.add_activity(Activity(1, "12:00", "12.12.2023", "description"))
        self.__repo.add_activity(Activity(2, "13:00", "13.12.2023", "description2"))

    def test_add_person(self):
        self.assertEqual(len(self.__repo.get_persons()), 2)
        self.__repo.add_person(Person(3, "John2", "1234"))
        self.assertEqual(len(self.__repo.get_persons()), 3)
        self.assertRaises(RepositoryException, self.__repo.add_person, Person(1, "John", "123"))

    def test_remove_person(self):
        self.assertEqual(len(self.__repo.get_persons()), 2)
        self.__repo.remove_person(1)
        self.assertEqual(len(self.__repo.get_persons()), 1)
        self.assertRaises(RepositoryException, self.__repo.remove_person, 3)

    def test_update_person(self):
        self.assertEqual(len(self.__repo.get_persons()), 2)
        self.__repo.update_person(1, "John2", "1234")
        self.assertEqual(len(self.__repo.get_persons()), 2)
        self.assertEqual(self.__repo.get_persons()[0].get_name(), "John2")
        self.assertEqual(self.__repo.get_persons()[0].get_phone(), "1234")
        self.assertRaises(RepositoryException, self.__repo.update_person, 3, "John2", "1234")

    def test_add_activity(self):
        self.assertEqual(len(self.__repo.get_activities()), 2)
        self.__repo.add_activity(Activity(3, "14:00", "14.12.2023", "description3"))
        self.assertEqual(len(self.__repo.get_activities()), 3)
        self.assertRaises(RepositoryException, self.__repo.add_activity, Activity(1, "12:00", "12.12.2023", "description"))

    def test_remove_activity(self):
        self.assertEqual(len(self.__repo.get_activities()), 2)
        self.__repo.remove_activity(1)
        self.assertEqual(len(self.__repo.get_activities()), 1)
        self.assertRaises(RepositoryException, self.__repo.remove_activity, 3)

    def test_update_activity(self):
        self.assertEqual(len(self.__repo.get_activities()), 2)
        self.__repo.update_activity(1, "14:00", "14.12.2023", "description3")
        self.assertEqual(len(self.__repo.get_activities()), 2)
        self.assertEqual(self.__repo.get_activities()[0].get_time(), "14:00")
        self.assertEqual(self.__repo.get_activities()[0].get_date(), "14.12.2023")
        self.assertEqual(self.__repo.get_activities()[0].get_description(), "description3")
        self.assertRaises(RepositoryException, self.__repo.update_activity, 3, "14:00", "14.12.2023", "description3")

    def test_assign_activity(self):
        self.assertEqual(len(self.__repo.get_activities()[0].get_person_id()), 0)
        self.__repo.assign_activity(1, 1)
        self.assertEqual(len(self.__repo.get_activities()[0].get_person_id()), 1)
        self.assertRaises(RepositoryException, self.__repo.assign_activity, 3, 1)
        self.assertRaises(RepositoryException, self.__repo.assign_activity, 1, 3)


if __name__ == '__main__':
    unittest.main()