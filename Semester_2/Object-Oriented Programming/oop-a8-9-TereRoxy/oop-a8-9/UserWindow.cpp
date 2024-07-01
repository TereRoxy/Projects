#include "UserWindow.h"

UserWindow::UserWindow(QWidget* parent)
	: QMainWindow(parent)
{
	backButton = new QPushButton("Back", this);
	seeEventsByMonthButton = new QPushButton("See events", this);
	getUserEventsButton = new QPushButton("Show my events", this);
	openUserListButton = new QPushButton("Open my list", this);
	saveUserListButton = new QPushButton("Save", this);
	nextEventButton = new QPushButton("Next", this);
	addEventButton = new QPushButton("Add", this);
	
	eventsList = new QListWidget;

	currentDisplayedEvent = new QListWidget;

	deleteEventEdit = new QLineEdit;
	monthEdit = new QLineEdit;
	deleteButton = new QPushButton("Delete", this);
	
	fileDialog = new SelectFileWindow(this);
	eventIterator = nullptr;
	
	setupUi();
	connectSignals();
}

UserWindow::~UserWindow()
{
	delete backButton;
	delete seeEventsByMonthButton;
	delete getUserEventsButton;
	delete openUserListButton;
	delete eventsList;
	delete deleteEventEdit;
	delete deleteButton;
	delete saveUserListButton;
	delete monthEdit;
	delete currentDisplayedEvent;
	delete addEventButton;
	delete nextEventButton;
	delete eventIterator;
}

void UserWindow::setupUi()
{
	this->setWindowTitle("User Window");
	this->resize(400, 200);

	QHBoxLayout* mainLayout = new QHBoxLayout;

	QLabel* monthLabel = new QLabel("Month: ", this);

	QHBoxLayout* monthLayout = new QHBoxLayout;
	monthLayout->addWidget(monthLabel);
	monthLayout->addWidget(monthEdit);
	monthLayout->addWidget(seeEventsByMonthButton);
	
	QHBoxLayout* deleteEventLayout = new QHBoxLayout;
	QLabel* deleteEventLabel = new QLabel("Title: ", this);
	deleteEventLayout->addWidget(deleteEventLabel);
	deleteEventLayout->addWidget(deleteEventEdit);
	deleteEventLayout->addWidget(deleteButton);
	
	QHBoxLayout* repoActionsLayout = new QHBoxLayout;
	repoActionsLayout->addWidget(addEventButton);
	repoActionsLayout->addWidget(nextEventButton);
	

	//set max length of current event 
	currentDisplayedEvent->setMaximumHeight(50);

	QVBoxLayout* leftLayout = new QVBoxLayout;
	leftLayout->addLayout(deleteEventLayout);
	leftLayout->addLayout(monthLayout);
	leftLayout->addWidget(currentDisplayedEvent);
	leftLayout->addLayout(repoActionsLayout);

	QGridLayout* actionButtonsLayout = new QGridLayout;
	actionButtonsLayout->addWidget(openUserListButton, 0, 0);
	actionButtonsLayout->addWidget(getUserEventsButton, 0, 1);
	actionButtonsLayout->addWidget(saveUserListButton, 1, 0);
	actionButtonsLayout->addWidget(backButton, 1, 1);

	QVBoxLayout* rightLayout = new QVBoxLayout;
	rightLayout->addWidget(eventsList);
	rightLayout->addLayout(actionButtonsLayout);

	mainLayout->addLayout(leftLayout);
	mainLayout->addLayout(rightLayout);
	
	QWidget* centralWidget = new QWidget;
	this->setCentralWidget(centralWidget);
	centralWidget->setLayout(mainLayout);
	
	centerWindow();
}

void UserWindow::connectSignals()
{
	QObject::connect(backButton, &QPushButton::clicked, this, &UserWindow::goBack);
	QObject::connect(seeEventsByMonthButton, &QPushButton::clicked, this, &UserWindow::handleSeeEventsByMonth);
	QObject::connect(getUserEventsButton, &QPushButton::clicked, this, &UserWindow::handleGetUserEvents);
	QObject::connect(openUserListButton, &QPushButton::clicked, this, &UserWindow::handleOpen);
	QObject::connect(saveUserListButton, &QPushButton::clicked, this, &UserWindow::handleSave);
	QObject::connect(deleteButton, &QPushButton::clicked, this, &UserWindow::handleDelete);
	QObject::connect(fileDialog, &SelectFileWindow::setCSV, this, &UserWindow::handleSaveCSV);
	QObject::connect(fileDialog, &SelectFileWindow::setHTML, this, &UserWindow::handleSaveHTML);
}

void UserWindow::handleDelete()
{
	QString title = deleteEventEdit->text();
	if (title.isEmpty())
	{
		QMessageBox::warning(this, "Error", "Title cannot be empty!");
		return;
	}
	try {
		Event ev = { 0, title.toStdString(), "", "", "", ""};
		service->deleteUserEvent(ev);
		QMessageBox::information(this, "Success", "Event was deleted successfully from the list of events you're interested in.");
	}
	catch (RepositoryException& e)
	{
		QMessageBox::warning(this, "Error", e.what());
		return;
	}
}

void UserWindow::handleGetUserEvents()
{
	eventsList->clear();
	std::vector<Event> events = service->getUserEvents();
	for (auto event : events)
	{
		std::string evString = event.toString();
		eventsList->addItem(evString.c_str());
	}
}

void UserWindow::handleOpen()
{
	if (filetype == "CSV") {
		std::string command = "start events.csv";
		std::system(command.c_str());
	}
	else if (filetype == "HTML")
	{
		std::string command = "start events.html";
		std::system(command.c_str());
	}
}

void UserWindow::handleSave()
{
	try 
	{ 
		service->saveUserList(filetype); 
		QMessageBox::information(this, "Success", "List saved!");
	}
	catch (RepositoryException& e) 
	{
		QMessageBox::warning(this, "Error", e.what());
		emit backToMain(); 
	}
}

void UserWindow::handleSeeEventsByMonth()
{
	std::string month = monthEdit->text().toStdString();
	if (month.empty())
	{
		QMessageBox::warning(this, "Error", "Month cannot be empty!");
		return;
	}
	currentDisplayedEvent->clear();
	monthEdit->clear();
	int monthInt;
	try {
		monthInt = std::stoi(month);
		if (monthInt < 1 || monthInt > 12)
		{
			QMessageBox::warning(this, "Error", "Month must be an integer between 1 and 12!");
			return;
		}
	}
	catch (exception& e)
	{
		QMessageBox::warning(this, "Error", "Month must be an integer between 1 and 12!");
		return;
	}

	//create an iterator for the events in the given month
	Service &serviceCopy = *service;
	if (eventIterator != nullptr)
		delete eventIterator;
	eventIterator = new MonthEventIterator(serviceCopy, monthInt);
	//get the first event in the given month
	if (eventIterator->valid())
	{
		Event ev = eventIterator->getCurrent();
		currentDisplayedEvent->addItem(ev.toString().c_str());
		connect(nextEventButton, &QPushButton::clicked, this, &UserWindow::handleNextEvent);
		connect(addEventButton, &QPushButton::clicked, this, &UserWindow::handleAddEvent);
		//open the link associated to the event
		std::string command = "start " + ev.getLink();
		std::system(command.c_str());
	}
	else
	{
		QMessageBox::information(this, "Info", "No events in this month!");
		disconnect(nextEventButton, &QPushButton::clicked, this, &UserWindow::handleNextEvent);
		disconnect(addEventButton, &QPushButton::clicked, this, &UserWindow::handleAddEvent);
	}
}

void UserWindow::handleNextEvent() {
	eventIterator->next();
	if (eventIterator->valid())
	{
		Event ev = eventIterator->getCurrent();
		currentDisplayedEvent->clear();
		currentDisplayedEvent->addItem(ev.toString().c_str());
		//open the link associated to the event
		std::string command = "start " + ev.getLink();
		std::system(command.c_str());
	}
	else
	{
		QMessageBox::information(this, "Info", "No more events to show!");
		disconnect(nextEventButton, &QPushButton::clicked, this, &UserWindow::handleNextEvent);
		disconnect(addEventButton, &QPushButton::clicked, this, &UserWindow::handleAddEvent);
	}
}

void UserWindow::handleAddEvent()
{
	if (eventIterator->valid())
	{
		Event ev = eventIterator->getCurrent();
		service->addUserEvent(ev);
		handleNextEvent();
	}
	else
	{
		QMessageBox::warning(this, "Oops!", "Something went wrong.");
	}
}

void UserWindow::centerWindow()
{
	QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
	int x = (screenGeometry.width() - width()) / 2;
	int y = (screenGeometry.height() - height()) / 2;
	move(x, y);
}

SelectFileWindow::SelectFileWindow(QWidget* parent)
	: QDialog(parent)
{

	CSVButton = new QPushButton("CSV", this);
	HTMLButton = new QPushButton("HTML", this);
	
	setupUi();
	connectSignals();
}

SelectFileWindow::~SelectFileWindow()
{
	delete CSVButton;
	delete HTMLButton;
}

void SelectFileWindow::setupUi()
{
	this->setWindowTitle("Select file type");
	this->resize(200, 100);

	QVBoxLayout* vLayout = new QVBoxLayout;
	QLabel* label = new QLabel("Choose the type of file you want to save your list of events to", this);
	vLayout->addWidget(label);
	
	QHBoxLayout* mainLayout = new QHBoxLayout;
	mainLayout->addWidget(CSVButton);
	mainLayout->addWidget(HTMLButton);

	vLayout->addLayout(mainLayout);

	QWidget* centralWidget = new QWidget;
	this->setLayout(vLayout);
}

void SelectFileWindow::connectSignals()
{
	QObject::connect(CSVButton, &QPushButton::clicked, this, &SelectFileWindow::handleCSV);
	QObject::connect(HTMLButton, &QPushButton::clicked, this, &SelectFileWindow::handleHTML);
}