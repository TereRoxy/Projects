from src.domain.expense import Expense
import pickle


class BaseRepository:
    def __init__(self, filename=None):
        self.filename = filename
        # self.save_expenses([])
        self.__history = []

    def add_expense(self, expense):
        """
        Adds an expense to the repository
        :param expense: to be added
        :return: None
        Raises exception if expense already in repo
        """
        expenses = self.get_expenses()
        if expense in expenses:
            raise ValueError("Expense already added to repo\n")
        else:
            self.update_history(expenses)
            expenses.append(expense)
            self.save_expenses(expenses)

    def get_expenses(self):
        """
        Returns all expenses in the repository
        :return: the list of expenses
        Raises exception if the repository file could not be found
        """
        expenses = []
        try:
            with open(self.filename, 'rb') as file:
                expenses = pickle.load(file)
        except FileNotFoundError:
            # raise FileNotFoundError("The repository file could not be found")
            pass
        return expenses

    def save_expenses(self, expenses):
        """
        Saves the expenses to the repository file
        :param expenses: the list of expenses to be saved
        :return: None
        """
        with open(self.filename, 'wb') as file:
            pickle.dump(expenses, file)

    def update_history(self, expenses):
        copy_expenses = []
        for expense in expenses:
            copy_expenses.append(expense)
        self.__history.append(copy_expenses)

    def undo_last_operation(self):
        if not self.__history:
            raise ValueError("No more undoes available.\n")
        else:
            last_operation = self.__history.pop()
            self.save_expenses(last_operation)


class MemoryRepository(BaseRepository):
    def __init__(self):
        super().__init__()
        self.__expenses = []

    def get_expenses(self):
        return self.__expenses

    def save_expenses(self, expenses):
        self.__expenses = expenses


class TextFileRepository(BaseRepository):
    def __init__(self):
        super().__init__("text_data.txt")

    def get_expenses(self):
        expenses = []
        try:
            with open(self.filename, 'r') as file:
                for line in file:
                    day, amount, expense_type = map(str.strip, line.split(','))
                    expenses.append(Expense(int(day), int(amount), expense_type))
        except FileNotFoundError:
            pass
        return expenses

    def save_expenses(self, expenses):
        with open(self.filename, 'w') as file:
            for exp in expenses:
                file.write(f"{exp.get_day()},{exp.get_amount()},{exp.get_expense_type()}\n")


class BinaryFileRepository(BaseRepository):
    def __init__(self, filename=None):
        if filename is None:
            filename = "binary_data.pkl"
        super().__init__(filename)


def test_repository():
    # choice 1
    # add 1 expense to empty repo
    day = 3
    amount = 114
    expense_type = "ExpenseSTH"
    expense = Expense(day, amount, expense_type)
    repository = BinaryFileRepository("test_pickle.pkl")
    repository.add_expense(expense)
    repository.save_expenses([expense])
    assert repository.get_expenses() == [expense]

    # choice 2
    assert repository.get_expenses() == [expense]

    # choice 3

    # choice 4
    repository.undo_last_operation()
    # check if undo works for empty repo
    try:
        repository.undo_last_operation()
        repository.undo_last_operation()
        assert False
    except ValueError:
        assert True
