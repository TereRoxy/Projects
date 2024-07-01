#include "UndoRedo.h"

void ActionAdd::executeUndo() const {
	repo.deleteEvent(repo.getIndex(addedEvent));
}

void ActionAdd::executeRedo() const {
	repo.addEvent(addedEvent);
}

void ActionRemove::executeUndo() const {
	repo.addEvent(removedEvent);
}

void ActionRemove::executeRedo() const {
	repo.deleteEvent(repo.getIndex(removedEvent));
}

void ActionUpdate::executeUndo() const {
	repo.updateEvent(oldEvent, repo.getIndex(newEvent));
}

void ActionUpdate::executeRedo() const {
	repo.updateEvent(newEvent, repo.getIndex(oldEvent));
}