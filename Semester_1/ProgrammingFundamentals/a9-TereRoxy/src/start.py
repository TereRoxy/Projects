import ui.ui as ui
import repository.repository as repository
import services.services as services
import services.undo_service as undo_service
from configparser import ConfigParser


def config_repo():
    config = ConfigParser()
    config.read("settings.properties")

    repo_type = config["Settings"]["repository"]
    persons_file = config["Settings"]["persons"]
    activities_file = config["Settings"]["activities"]

    if repo_type == "memory":
        repo = repository.MemoryRepo()
    elif repo_type == "binary":
        repo = repository.PickleRepo(persons_file, activities_file)
    elif repo_type == "textfile":
        repo = repository.FileRepo(persons_file, activities_file)
    else:
        raise ValueError("Invalid repository type!")
    return repo


def main():
    repo = config_repo()
    undo = undo_service.UndoService()
    manager = services.Manager(repo, undo)
    statistics = services.Statistics(repo)

    if repo.get_persons() == [] or repo.get_activities() == []:
        services.GenerateActivities(repo)
        services.GeneratePersons(repo)
        services.AssignActivities(repo)
        repo.save_file()

    undo.__init__()

    console_ui = ui.UI()
    console_ui.run(manager, statistics, undo)


if __name__ == "__main__":
    main()
