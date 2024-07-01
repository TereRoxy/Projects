class Expense:
    def __init__(self, day: int, amount: int, expense_type: str):

        if day < 1 or day > 30:
            raise ValueError("Day must be between 1 and 30")
        else:
            self.__day = day

        if amount < 1:
            raise ValueError("Amount must be positive")
        else:
            self.__amount = amount

        self.__expense_type = expense_type

    def get_day(self):
        return self.__day

    def get_amount(self):
        return self.__amount

    def get_expense_type(self):
        return self.__expense_type

    def __eq__(self, other):
        return self.__day == other.__day and self.__amount == other.__amount and self.__expense_type == other.__expense_type

    def __str__(self):
        return f"Day: {self.__day}, Amount: {self.__amount}, Type: {self.__expense_type}"


def test_domain():
    day = 1
    amount = 100
    expense_type = "Expense1"
    expense = Expense(day, amount, expense_type)
    assert expense.get_day() == day
    assert expense.get_amount() == amount
    assert expense.get_expense_type() == expense_type
    assert str(expense) == f"Day: {day}, Amount: {amount}, Type: {expense_type}"

    expense2 = Expense(day, amount, expense_type)
    assert expense == expense2

    expense3 = Expense(2, 200, "Expense2")
    assert expense != expense3

    try:
        Expense(0, 100, "Expense1")
        assert False
    except ValueError:
        assert True

    try:
        Expense(1, -100, "Expense1")
        assert False
    except ValueError:
        assert True
