#pragma once
#include <QtWidgets>
#include <QScreen>
#include "Service.h"
#include "Validator.h"

class AdminWindow : public QMainWindow
{
	Q_OBJECT

public:
	AdminWindow(QWidget* parent = nullptr);
	~AdminWindow();
	void setService(Service* serv) { service = serv; }

signals:
	void backToMain();

private slots:
	void handleDeleteEvent();
	void handleViewEvents();
	void handleEditEvent();
	void handleCancel();
	void handleSaveChanges();
	void handleUndo();
	void handleRedo();
	void goBack() {
		emit backToMain();
	};
private:
	void setupUi();
	void connectSignals();
	void centerWindow();
	
	Service* service;

	// Declare UI elements
	QPushButton* addEventButton;
	QPushButton* updateEventButton;
	QPushButton* deleteEventButton;
	QPushButton* viewEventsButton;
	QPushButton* backButton;

	QPushButton* undoButton;
	QPushButton* redoButton;
	
	QListWidget* eventsList;
	
	QLineEdit* titleEdit;
	QLineEdit* descriptionEdit;
	QLineEdit* dateEdit;
	QLineEdit* timeEdit;
	QLineEdit* linkEdit;
	QLineEdit* participantsEdit;
	
	QLineEdit* titleDeleteEdit;
	
	QPushButton* saveButton;
	QPushButton* cancelButton;

	QShortcut* undoShortcut;
	QShortcut* redoShortcut;
	
};