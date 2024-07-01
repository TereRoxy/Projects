"""
2. Expenses
Manage a list of expenses. Each expense has a day (integer between 1 and 30), amount of money (positive integer) and
expense type (string). Provide the following features:

1. Add an expense. Expense data is read from the console.
2. Display the list of expenses.
3. Filter the list so that it contains only expenses above a certain value read from the console.
4. Undo the last operation that modified program data. This step can be repeated. The user can undo only those
operations made during the current run of the program.

"""
from src.domain.expense import Expense, test_domain
from src.repository.repository import *
from src.services.services import Services, test_services
from src.ui.ui import UI


# Generate initial list of expenses
def initialize_repository(repo: str):
    if repo == "text_file":
        text_file_repo = TextFileRepository()
        init_repo = text_file_repo
    elif repo == "binary_file":
        binary_file_repo = BinaryFileRepository()
        init_repo = binary_file_repo
    elif repo == "memory":
        memory_repo = MemoryRepository()
        init_repo = memory_repo
    else:
        raise ValueError("Invalid repository chosen")

    # Initialize with 10 programmatically generated entries
    for i in range(1, 11):
        try:
            init_repo.add_expense(Expense(i, i * 100, f"Expense{i}"))
        except ValueError:
            pass

    return init_repo


def test_all():
    test_domain()
    test_repository()
    test_services()


if __name__ == "__main__":
    test_all()

    repo = initialize_repository("text_file")   # Change repository type here ("text_file", "binary_file", "memory")
    services = Services(repo)
    ui = UI(services)
    ui.run()
