#include "AdminWindow.h"

AdminWindow::AdminWindow(QWidget* parent)
	: QMainWindow(parent)
{
	addEventButton = new QPushButton("Add a new event", this);
	updateEventButton = new QPushButton("Update an event", this);
	deleteEventButton = new QPushButton("Delete event", this);
	viewEventsButton = new QPushButton("Show all", this);
	backButton = new QPushButton("Back", this);
	
	eventsList = new QListWidget;
	
	titleEdit = new QLineEdit;
	descriptionEdit = new QLineEdit;
	dateEdit = new QLineEdit;
	timeEdit = new QLineEdit;
	linkEdit = new QLineEdit;
	participantsEdit = new QLineEdit;

	titleDeleteEdit = new QLineEdit;
	saveButton = new QPushButton("Save changes", this);
	cancelButton = new QPushButton("Cancel", this);
	
	setupUi();
	connectSignals();
}

AdminWindow::~AdminWindow()
{
	delete addEventButton;
	delete updateEventButton;
	delete deleteEventButton;
	delete viewEventsButton;
	delete backButton;
	delete eventsList;
	delete titleEdit;
	delete descriptionEdit;
	delete dateEdit;
	delete timeEdit;
	delete linkEdit;
	delete participantsEdit;
	delete saveButton;
	delete cancelButton;
	delete titleDeleteEdit;
}

void AdminWindow::setupUi()
{
	// Create main layout
	QHBoxLayout* mainLayout = new QHBoxLayout;
	//Left side layout
	QVBoxLayout* leftSide = new QVBoxLayout;

	//Create form layout
	QFormLayout* formLayout = new QFormLayout;
	leftSide->addLayout(formLayout);

	//Add labels and input fields to form layout
	QLabel* titleLabel = new QLabel("Title: ", this);
	formLayout->addRow(titleLabel, titleEdit);
	QLabel* descriptionLabel = new QLabel("Description: ", this);
	formLayout->addRow(descriptionLabel, descriptionEdit);
	QLabel* dateLabel = new QLabel("Date (YYYY-MM-DD): ", this);
	formLayout->addRow(dateLabel, dateEdit);
	QLabel* timeLabel = new QLabel("Time (HH:MM): ", this);
	formLayout->addRow(timeLabel, timeEdit);
	QLabel* linkLabel = new QLabel("Link: ");
	formLayout->addRow(linkLabel, linkEdit);
	QLabel* participantsLabel = new QLabel("Participants: ", this);
	formLayout->addRow(participantsLabel, participantsEdit);


	//Add/Update buttons
	QHBoxLayout* addUpdateLayout = new QHBoxLayout;
	addUpdateLayout->addWidget(addEventButton);
	addUpdateLayout->addWidget(updateEventButton);
	addUpdateLayout->addWidget(cancelButton);

	leftSide->addLayout(addUpdateLayout);

	//Delete layout
	QHBoxLayout* deleteLayout = new QHBoxLayout;
	QLabel* deleteTitleLabel = new QLabel("Title: ");
	deleteLayout->addWidget(deleteTitleLabel);
	deleteLayout->addWidget(titleDeleteEdit);
	deleteLayout->addWidget(deleteEventButton);

	leftSide->addLayout(deleteLayout);

	QVBoxLayout* rightSide = new QVBoxLayout;
	rightSide->addWidget(eventsList);

	QHBoxLayout* ShowSaveBackL = new QHBoxLayout;
	ShowSaveBackL->addWidget(viewEventsButton);
	ShowSaveBackL->addWidget(saveButton);
	ShowSaveBackL->addWidget(backButton);
	
	rightSide->addLayout(ShowSaveBackL);

	mainLayout->addLayout(leftSide);
	mainLayout->addLayout(rightSide);

	// Create central widget and set main layout
	QWidget* centralWidget = new QWidget;
	centralWidget->setLayout(mainLayout);
	setCentralWidget(centralWidget);

	// Set window title and size
	setWindowTitle("Admin Mode");
	resize(800, 400);
	centerWindow();
}

void AdminWindow::connectSignals()
{
	// Connect buttons to slots
	connect(addEventButton, &QPushButton::clicked, this, &AdminWindow::handleEditEvent);
	connect(updateEventButton, &QPushButton::clicked, this, &AdminWindow::handleEditEvent);
	connect(deleteEventButton, &QPushButton::clicked, this, &AdminWindow::handleDeleteEvent);
	connect(viewEventsButton, &QPushButton::clicked, this, &AdminWindow::handleViewEvents);
	connect(cancelButton, &QPushButton::clicked, this, &AdminWindow::handleCancel);
	connect(saveButton, &QPushButton::clicked, this, &AdminWindow::handleSaveChanges);
	connect(backButton, &QPushButton::clicked, this, &AdminWindow::goBack);
}

void AdminWindow::handleEditEvent()
{
	// Get input data
	QString title = titleEdit->text();
	QString description = descriptionEdit->text();
	QString date = dateEdit->text();
	QString time = timeEdit->text();
	QString link = linkEdit->text();
	QString participants = participantsEdit->text();

	// Validate input data
	if (title.isEmpty() || description.isEmpty() || date.isEmpty() || time.isEmpty() || link.isEmpty() || participants.isEmpty())
	{
		QMessageBox::warning(this, "Error", "Please fill in all fields");
		return;
	}
	
	// Convert QStrings to std::strings
	std::string titleStr = title.toStdString();
	std::string descriptionStr = description.toStdString();
	std::string dateStr = date.toStdString();
	std::string timeStr = time.toStdString();
	std::string linkStr = link.toStdString();
	std::string participantsStr = participants.toStdString();
	int participantsInt;
	
	//Validate input data format
	try {
		participantsInt = std::stoi(participantsStr);
		EventValidator ev;
		ev.validateEvent(titleStr, descriptionStr, dateStr, timeStr, linkStr, participantsInt);
	}
	catch (std::invalid_argument& e)
	{
		QMessageBox::warning(this, "Error", "Participants must be a number");
		return;
	}
	catch (ValidationException& e)
	{
		QMessageBox::warning(this, "Error", e.what());
		return;
	}

	// Call service function to add/update the repository according to sender button
	if (sender() == addEventButton)
	{
		try {
			service->addEvent(titleStr, descriptionStr, dateStr, timeStr, linkStr, participantsInt);
			
		}
		catch (std::exception& e)
		{
			QMessageBox::warning(this, "Error", e.what());
			return;
		}
	}
	else
	{
		try {
			service->updateEvent(titleStr, descriptionStr, dateStr, timeStr, linkStr, participantsInt);
		}
		catch (std::exception& e)
		{
			QMessageBox::warning(this, "Error", e.what());
			return;
		}
	}
	
	// Show success message
	QMessageBox::information(this, "Success", "Event saved successfully");

	// Clear input fields
	titleEdit->clear();
	descriptionEdit->clear();
	dateEdit->clear();
	timeEdit->clear();
	linkEdit->clear();
	participantsEdit->clear();
}

void AdminWindow::handleCancel() 
{
	// Clear input fields
	titleEdit->clear();
	descriptionEdit->clear();
	dateEdit->clear();
	timeEdit->clear();
	linkEdit->clear();
	participantsEdit->clear();
}

void AdminWindow::handleSaveChanges() 
{
	service->saveAdminList();
	QMessageBox::information(this, "Success", "Changes saved successfully!");
}

void AdminWindow::handleDeleteEvent()
{
	QString title = titleDeleteEdit->text();
	if (title.isEmpty())
	{
		QMessageBox::warning(this, "Error", "Please fill in the title field");
		return;
	}
	std::string titleStr = title.toStdString();
	try {
		service->deleteEvent(titleStr);
	}
	catch (RepositoryException& e)
	{
		QMessageBox::warning(this, "Error", e.what());
		return;
	}
	QMessageBox::information(this, "Success", "Event deleted successfully!");
}

void AdminWindow::handleViewEvents()
{
	// Clear the list widget
	eventsList->clear();
	//Add the events to the list widget
	vector<Event> all = service->getEvents();
	for (auto ev : all)
	{
		eventsList->addItem(ev.toString().c_str());
	}

}

void AdminWindow::centerWindow()
{
	QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
	int x = (screenGeometry.width() - width()) / 2;
	int y = (screenGeometry.height() - height()) / 2;
	move(x, y);
}
