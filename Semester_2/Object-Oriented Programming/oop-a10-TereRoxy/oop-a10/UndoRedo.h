#pragma once
#include "Repository.h"
#include "Event.h"

class Action {
public:
	virtual void executeUndo() const = 0;
	virtual void executeRedo() const = 0;
};

class ActionAdd : public Action {
private:
	Event& addedEvent;
	Repository& repo;
public:
	ActionAdd(Event& e, Repository& r) : addedEvent{ e }, repo{ r } {}
	void executeUndo() const override;
	void executeRedo() const override;
};

class ActionRemove : public Action {
private:
	Event& removedEvent;
	Repository& repo;
public:
	ActionRemove(Event& e, Repository& r) : removedEvent{ e }, repo{ r } {}
	void executeUndo() const override;
	void executeRedo() const override;
};

class ActionUpdate : public Action {
private:
	Event& oldEvent;
	Event& newEvent;
	Repository& repo;
public:
	ActionUpdate(Event& oldE, Event& newE, Repository& r) : oldEvent{ oldE }, newEvent{ newE }, repo{ r } {}
	void executeUndo() const override;
	void executeRedo() const override;
};