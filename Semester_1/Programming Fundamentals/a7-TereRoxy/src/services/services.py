from src.domain.expense import Expense
from src.repository.repository import *


class Services:
    def __init__(self, repository: BaseRepository):
        self.repository = repository

    def add_expense(self, day, amount, expense_type):
        try:
            expense = Expense(day, amount, expense_type)
            self.repository.add_expense(expense)
        except ValueError:
            pass

    def get_expenses(self):
        return self.repository.get_expenses()

    def filter_expenses(self, min_amount):
        new_expenses = []
        all_expenses = self.repository.get_expenses()
        self.repository.update_history(all_expenses)

        for expense in all_expenses:
            if expense.get_amount() >= min_amount:
                new_expenses.append(expense)

        self.repository.save_expenses(new_expenses)
        return new_expenses

    def undo_last_operation(self):
        self.repository.undo_last_operation()


def test_services():
    # choice 1
    day = 1
    amount = 100
    expense_type = "Expense1"
    expense = Expense(day, amount, expense_type)
    repository = BinaryFileRepository("test_binary_data.pkl")
    services = Services(repository)
    services.add_expense(day, amount, expense_type)
    assert services.get_expenses() == [expense]

    # choice 2
    assert services.get_expenses() == [expense]

    # choice 3
    min_amount = 50
    assert services.filter_expenses(min_amount) == [expense]

