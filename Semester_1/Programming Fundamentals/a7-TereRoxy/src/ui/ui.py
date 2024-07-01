

class UI:
    def __init__(self, services):
        self.services = services

    @staticmethod
    def show_menu():
        print("1. Add Expense")
        print("2. Display Expenses")
        print("3. Filter Expenses")
        print("4. Undo Last Operation")
        print("0. Exit")

    def run(self):
        while True:
            self.show_menu()
            choice = input("Enter your choice: ")
            if choice == '1':
                try:
                    day = int(input("Enter day: "))
                    amount = int(input("Enter amount: "))
                    expense_type = input("Enter expense type: ")
                    self.services.add_expense(day, amount, expense_type)
                except ValueError as ve:
                    print(str(ve) + "Invalid expense data. Please try again.")

            elif choice == '2':
                expenses = self.services.get_expenses()
                for expense in expenses:
                    print(expense)

            elif choice == '3':
                try:
                    min_amount = int(input("Enter minimum amount: "))
                    filtered_expenses = self.services.filter_expenses(min_amount)
                    for expense in filtered_expenses:
                        print(expense)
                except ValueError as ve:
                    print(str(ve) + "Invalid minimum amount. Please try again.")

            elif choice == '4':
                try:
                    self.services.undo_last_operation()
                except ValueError as ve:
                    print(str(ve))

            elif choice == '0':
                break
            else:
                print("Invalid choice. Please try again.")
