import unittest
from src.domain.domain import Person, Activity

class TestPerson(unittest.TestCase):
    def setUp(self):
        pass

    def test_create_person(self):
        person = Person(1, "John", "123")
        self.assertEqual(person.get_person_id(), 1)
        self.assertEqual(person.get_name(), "John")
        self.assertEqual(person.get_phone(), "123")

    def test_set_attributes(self):
        person = Person(1, "John", "123")
        person.set_name("John2")
        person.set_phone("1234")
        person.set_person_id(2)
        self.assertEqual(person.get_person_id(), 2)
        self.assertEqual(person.get_name(), "John2")
        self.assertEqual(person.get_phone(), "1234")


class TestActivity(unittest.TestCase):
    def setUp(self):
        pass

    def test_create_activity(self):
        activity = Activity(1, "12:00", "12.12.2023", "description")
        self.assertEqual(activity.get_activity_id(), 1)
        self.assertEqual(activity.get_time(), "12:00")
        self.assertEqual(activity.get_date(), "12.12.2023")
        self.assertEqual(activity.get_description(), "description")

    def test_add_person_id(self):
        activity = Activity(1, "12:00", "12.12.2023", "description")
        activity.add_person_id(1)
        self.assertEqual(activity.get_person_id(), [1])
        activity.add_person_id(2)
        self.assertEqual(activity.get_person_id(), [1, 2])

    def test_set_attributes(self):
        activity = Activity(1, "12:00", "12.12.2023", "description")
        activity.set_activity_id(2)
        activity.set_time("13:00")
        activity.set_date("13.12.2023")
        activity.set_description("description2")
        self.assertEqual(activity.get_activity_id(), 2)
        self.assertEqual(activity.get_time(), "13:00")
        self.assertEqual(activity.get_date(), "13.12.2023")
        self.assertEqual(activity.get_description(), "description2")


if __name__ == '__main__':
    unittest.main()
