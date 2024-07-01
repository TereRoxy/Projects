import ui.ui as ui
import repository.repository as repository
import services.services as services


def main():
    repo = repository.MemoryRepo()
    manager = services.Manager(repo)
    statistics = services.Statistics(repo)

    services.GenerateActivities(repo)
    services.GeneratePersons(repo)
    services.AssignActivities(repo)

    console_ui = ui.UI()
    console_ui.run(manager, statistics)


if __name__ == "__main__":
    main()
