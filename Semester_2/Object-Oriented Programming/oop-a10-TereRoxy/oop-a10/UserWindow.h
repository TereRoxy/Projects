#pragma once
#include <QtWidgets>
#include "Service.h"
#include "Validator.h"
#include "UserEventsWindow.h"

class SelectFileWindow : public QDialog
{
	Q_OBJECT
public:
	SelectFileWindow(QWidget* parent = nullptr);
	~SelectFileWindow();

signals:
	void setCSV();
	void setHTML();

private slots:
	void handleCSV() { emit setCSV(); };
	void handleHTML() { emit setHTML(); }

private:
	void setupUi();
	void connectSignals();
	QPushButton* CSVButton;
	QPushButton* HTMLButton;
};

class UserWindow : public QMainWindow
{
	Q_OBJECT
public:
	UserWindow(QWidget* parent = nullptr);
	~UserWindow();
	void setService(Service* serv) { service = serv; }
	void showWithDialog() { this->show(); fileDialog->show(); };
signals:
	void backToMain();
	
private slots:
	void goBack() {
		emit backToMain();
	};
	void handleSave();
	void handleOpen();
	void handleDelete();
	void handleSeeEventsByMonth();
	void handleGetUserEvents();
	void handleAddEvent();
	void handleNextEvent();

	void showUserEventsWindow();

	void handleSaveCSV() { filetype = "CSV"; fileDialog->close(); };
	void handleSaveHTML() { filetype = "HTML"; fileDialog->close(); };

private:
	Service* service;
	void setupUi();
	void connectSignals();
	void centerWindow();

	MonthEventIterator* eventIterator;

	SelectFileWindow* fileDialog;

	UserEventsWindow* userEventsWindow;

	// Declare UI elements
	QPushButton* backButton;
	QPushButton* seeEventsByMonthButton;
	QPushButton* getUserEventsButton;
	QPushButton* openUserListButton;
	QPushButton* saveUserListButton;
	QPushButton* addEventButton;
	QPushButton* nextEventButton;

	QPushButton* deleteButton;
	
	QListWidget* eventsList;
	QListWidget* currentDisplayedEvent;

	QLineEdit* deleteEventEdit;
	QLineEdit* monthEdit;

	std::string filetype = "";
};